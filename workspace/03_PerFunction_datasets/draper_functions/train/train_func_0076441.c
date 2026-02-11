init_infile(lame_t gfp, char const *inPath)
{
    int     enc_delay = 0, enc_padding = 0;

    global. count_samples_carefully = 0;
    global. num_samples_read = 0;
    global. pcmbitwidth = global_raw_pcm.in_bitwidth;
    global. pcmswapbytes = global_reader.swapbytes;
    global. pcm_is_unsigned_8bit = global_raw_pcm.in_signed == 1 ? 0 : 1;
    global. pcm_is_ieee_float = 0;
    global. hip = 0;
    global. music_in = 0;
    global. snd_file = 0;
    global. in_id3v2_size = 0;
    global. in_id3v2_tag = 0;
    if (is_mpeg_file_format(global_reader.input_format)) {
        global. music_in = open_mpeg_file(gfp, inPath, &enc_delay, &enc_padding);
    }
    else {
#ifdef LIBSNDFILE
        if (strcmp(inPath, "-") != 0) {
            global. snd_file = open_snd_file(gfp, inPath);
        }
#endif
        if (global.snd_file == 0) {
            global. music_in = open_wave_file(gfp, inPath, &enc_delay, &enc_padding);
        }
    }
    initPcmBuffer(&global.pcm32, sizeof(int));
    initPcmBuffer(&global.pcm16, sizeof(short));
    setSkipStartAndEnd(gfp, enc_delay, enc_padding);
    {
        unsigned long n = lame_get_num_samples(gfp);
        if (n != MAX_U_32_NUM) {
            unsigned long const discard = global.pcm32.skip_start + global.pcm32.skip_end;
            lame_set_num_samples(gfp, n > discard ? n - discard : 0);
        }
    }
    return (global.snd_file != NULL || global.music_in != NULL) ? 1 : -1;
}
