mpeg_hdr_parse(const uint8_t *data, struct mpeg_audio_hdr *h) {
    struct mpeg_audio_hdr hz = {0};
    uint32_t hh;
    int i;

    *h = hz;

    if (data[0] != 0xff || (data[1] & 0xe0) != 0xe0)
        return 0;

    hh = (data[1] << 16) | (data[2] << 8) | data[3];


    switch (bits(hh, 20, 19)) {
        case 0: h->version = m_vers_2_5;    break;
        case 2: h->version = m_vers_2;      break;
        case 3: h->version = m_vers_1;      break;

        default:    return 0;
    }


    switch (bits(hh, 18, 17)) {
        case 1: h->layer = m_layer_3;       break;
        case 2: h->layer = m_layer_2;       break;
        case 3: h->layer = m_layer_1;       break;

        default:    return 0;
    }


    h->has_crc = bits(hh, 16, 16);
    if (h->has_crc)
        h->crc = (data[5] << 8) | (data[6]);


    i = (h->version == m_vers_1) ? 0 : 3;
    i += h->layer - 1;
    if (i == 5) i = 4;
    h->bitrate = bitrate_tbl[bits(hh, 15, 12)][i];
    if (h->bitrate == -1)
        return 0;


    i = h->version - 1;
    h->samplerate = samplerate_tbl[bits(hh, 11, 10)][i];
    if (h->samplerate == - 1)
        return 0;


    h->padded = bits(hh, 9, 9);


    h->channels = bits(hh, 7, 6);


    h->mode_extn = bits(hh, 5, 4);

    h->copyr = bits(hh, 3, 3);
    h->original = bits(hh, 2, 2);
    h->emph = bits(hh, 1, 0);

    return 1;
}
