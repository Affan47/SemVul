decoder_progress(DecoderProgress dp, const mp3data_struct * mp3data, int iread)
{
    addSamples(dp, iread);

    console_printf("\rFrame#%6i/%-6i %3i kbps",
                   dp->frame_ctr, dp->frames_total, mp3data->bitrate);


    if (mp3data->mode == JOINT_STEREO) {
        int     curr = mp3data->mode_ext;
        int     last = dp->last_mode_ext;
        console_printf("  %s  %c",
                       curr & 2 ? last & 2 ? " MS " : "LMSR" : last & 2 ? "LMSR" : "L  R",
                       curr & 1 ? last & 1 ? 'I' : 'i' : last & 1 ? 'i' : ' ');
        dp->last_mode_ext = curr;
    }
    else {
        console_printf("         ");
        dp->last_mode_ext = 0;
    }

    console_printf("        \b\b\b\b\b\b\b\b");
    console_flush();
}
