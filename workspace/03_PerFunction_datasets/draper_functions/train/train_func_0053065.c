S_SetMusicVolume(void)
{
    if (cdmusic)
    {
        I_CDMusSetVolume(snd_MusicVolume * 16);
    }
    else
    {
        I_SetMusicVolume(snd_MusicVolume * 8);
    }
    if (snd_MusicVolume == 0)
    {
        if (!cdmusic)
        {
            I_PauseSong();
        }
        MusicPaused = true;
    }
    else if (MusicPaused)
    {
        if (!cdmusic)
        {
            I_ResumeSong();
        }
        MusicPaused = false;
    }
}
