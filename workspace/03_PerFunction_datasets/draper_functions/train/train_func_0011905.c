OpenSndFile(lame_global_flags * gfp, char *inPath, int *enc_delay, int *enc_padding)
{
    FILE   *musicin;


    lame_set_num_samples(gfp, MAX_U_32_NUM);


    if (!strcmp(inPath, "-")) {
        lame_set_stream_binary_mode(musicin = stdin);
    }
    else {
        if ((musicin = fopen(inPath, "rb")) == NULL) {
            if (silent < 10) {
                error_printf("Could not find \"%s\".\n", inPath);
            }
            exit(1);
        }
    }

    if (is_mpeg_file_format(input_format)) {
#ifdef AMIGA_MPEGA
        if (-1 == lame_decode_initfile(inPath, &mp3input_data)) {
            if (silent < 10) {
                error_printf("Error reading headers in mp3 input file %s.\n", inPath);
            }
            exit(1);
        }
#endif
#ifdef HAVE_MPGLIB
        if (-1 == lame_decode_initfile(musicin, &mp3input_data, enc_delay, enc_padding)) {
            if (silent < 10) {
                error_printf("Error reading headers in mp3 input file %s.\n", inPath);
            }
            exit(1);
        }
#endif
        if (-1 == lame_set_num_channels(gfp, mp3input_data.stereo)) {
            if (silent < 10) {
                error_printf("Unsupported number of channels: %ud\n", mp3input_data.stereo);
            }
            exit(1);
        }
        (void) lame_set_in_samplerate(gfp, mp3input_data.samplerate);
        (void) lame_set_num_samples(gfp, mp3input_data.nsamp);
    }
    else if (input_format == sf_ogg) {
        if (silent < 10) {
            error_printf("sorry, vorbis support in LAME is deprecated.\n");
        }
        exit(1);
    }
    else if (input_format == sf_raw) {

        if (silent < 10) {
            console_printf("Assuming raw pcm input file");
            if (swapbytes)
                console_printf(" : Forcing byte-swapping\n");
            else
                console_printf("\n");
        }
        global. pcmswapbytes = swapbytes;
    }
    else {
        input_format = parse_file_header(gfp, musicin);
    }
    if (input_format == sf_unknown) {
        exit(1);
    }


    if (lame_get_num_samples(gfp) == MAX_U_32_NUM && musicin != stdin) {

        double  flen = lame_get_file_size(inPath);
        if (flen >= 0) {

            if (is_mpeg_file_format(input_format)) {
                if (mp3input_data.bitrate > 0) {
                    double  totalseconds = (flen * 8.0 / (1000.0 * mp3input_data.bitrate));
                    unsigned long tmp_num_samples =
                        (unsigned long) (totalseconds * lame_get_in_samplerate(gfp));

                    (void) lame_set_num_samples(gfp, tmp_num_samples);
                    mp3input_data.nsamp = tmp_num_samples;
                }
            }
            else {
                (void) lame_set_num_samples(gfp,
                                            (unsigned long) (flen /
                                                             (2 * lame_get_num_channels(gfp))));
            }
        }
    }
    return musicin;
}
