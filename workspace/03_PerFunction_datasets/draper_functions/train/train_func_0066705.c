ipvideo_decode_init(AVCodecContext *avctx)
{
    IpvideoContext *s = avctx->priv_data;

    s->avctx = avctx;

    if (s->avctx->palctrl == NULL) {
        av_log(avctx, AV_LOG_ERROR, " Interplay video: palette expected.\n");
        return -1;
    }

    avctx->pix_fmt = PIX_FMT_PAL8;
    dsputil_init(&s->dsp, avctx);


    s->decoding_map_size = avctx->width * avctx->height / (8 * 8 * 2);


    ipvideo_decode_block[0x0] = ipvideo_decode_block_opcode_0x0;
    ipvideo_decode_block[0x1] = ipvideo_decode_block_opcode_0x1;
    ipvideo_decode_block[0x2] = ipvideo_decode_block_opcode_0x2;
    ipvideo_decode_block[0x3] = ipvideo_decode_block_opcode_0x3;
    ipvideo_decode_block[0x4] = ipvideo_decode_block_opcode_0x4;
    ipvideo_decode_block[0x5] = ipvideo_decode_block_opcode_0x5;
    ipvideo_decode_block[0x6] = ipvideo_decode_block_opcode_0x6;
    ipvideo_decode_block[0x7] = ipvideo_decode_block_opcode_0x7;
    ipvideo_decode_block[0x8] = ipvideo_decode_block_opcode_0x8;
    ipvideo_decode_block[0x9] = ipvideo_decode_block_opcode_0x9;
    ipvideo_decode_block[0xA] = ipvideo_decode_block_opcode_0xA;
    ipvideo_decode_block[0xB] = ipvideo_decode_block_opcode_0xB;
    ipvideo_decode_block[0xC] = ipvideo_decode_block_opcode_0xC;
    ipvideo_decode_block[0xD] = ipvideo_decode_block_opcode_0xD;
    ipvideo_decode_block[0xE] = ipvideo_decode_block_opcode_0xE;
    ipvideo_decode_block[0xF] = ipvideo_decode_block_opcode_0xF;

    s->current_frame.data[0] = s->last_frame.data[0] =
    s->second_last_frame.data[0] = NULL;

    return 0;
}
