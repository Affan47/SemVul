decode_wave_header(AVCodecContext *avctx, uint8_t *header, int header_size)
{
    GetBitContext hb;
    int len;
    int chunk_size;
    short wave_format;

    init_get_bits(&hb, header, header_size*8);
    if (get_le32(&hb) != MKTAG('R','I','F','F')) {
        av_log(avctx, AV_LOG_ERROR, "missing RIFF tag\n");
        return -1;
    }

    chunk_size = get_le32(&hb);

    if (get_le32(&hb) != MKTAG('W','A','V','E')) {
        av_log(avctx, AV_LOG_ERROR, "missing WAVE tag\n");
        return -1;
    }

    while (get_le32(&hb) != MKTAG('f','m','t',' ')) {
        len = get_le32(&hb);
        skip_bits(&hb, 8*len);
    }
    len = get_le32(&hb);

    if (len < 16) {
        av_log(avctx, AV_LOG_ERROR, "fmt chunk was too short\n");
        return -1;
    }

    wave_format = get_le16(&hb);

    switch (wave_format) {
        case WAVE_FORMAT_PCM:
            break;
        default:
            av_log(avctx, AV_LOG_ERROR, "unsupported wave format\n");
            return -1;
    }

    avctx->channels = get_le16(&hb);
    avctx->sample_rate = get_le32(&hb);
    avctx->bit_rate = get_le32(&hb) * 8;
    avctx->block_align = get_le16(&hb);
    avctx->bits_per_coded_sample = get_le16(&hb);

    if (avctx->bits_per_coded_sample != 16) {
        av_log(avctx, AV_LOG_ERROR, "unsupported number of bits per sample\n");
        return -1;
    }

    len -= 16;
    if (len > 0)
        av_log(avctx, AV_LOG_INFO, "%d header bytes unparsed\n", len);

    return 0;
}
