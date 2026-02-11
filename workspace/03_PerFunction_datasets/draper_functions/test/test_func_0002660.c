init_atrac3_transforms(ATRAC3Context *q) {
    float enc_window[256];
    float s;
    int i;


    for (i=0 ; i<256; i++)
        enc_window[i] = (sin(((i + 0.5) / 256.0 - 0.5) * M_PI) + 1.0) * 0.5;

    if (!mdct_window[0])
        for (i=0 ; i<256; i++) {
            mdct_window[i] = enc_window[i]/(enc_window[i]*enc_window[i] + enc_window[255-i]*enc_window[255-i]);
            mdct_window[511-i] = mdct_window[i];
        }


    for (i=0 ; i<24; i++) {
        s = qmf_48tap_half[i] * 2.0;
        qmf_window[i] = s;
        qmf_window[47 - i] = s;
    }


    ff_mdct_init(&mdct_ctx, 9, 1);
}
