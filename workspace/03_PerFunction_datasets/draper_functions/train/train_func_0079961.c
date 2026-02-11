close_audio_file(audio_file *aufile)
{
    if ((aufile->fileType == OUTPUT_WAV) && (aufile->toStdio == 0))
    {
        fseek(aufile->sndfile, 0, SEEK_SET);

        if (aufile->channelMask)
            write_wav_extensible_header(aufile, aufile->channelMask);
        else
            write_wav_header(aufile);
    }

    if (aufile->toStdio == 0)
        fclose(aufile->sndfile);

    if (aufile) free(aufile);
}
