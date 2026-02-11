S_ChangeMusic(int musicnum, int looping)
{
    musicinfo_t *music = NULL;
    char namebuf[9];
    void *handle;


    if (musicnum == mus_intro && (snd_musicdevice == SNDDEVICE_ADLIB
                               || snd_musicdevice == SNDDEVICE_SB))
    {
        musicnum = mus_introa;
    }

    if (musicnum <= mus_None || musicnum >= NUMMUSIC)
    {
        I_Error("Bad music number %d", musicnum);
    }
    else
    {
        music = &S_music[musicnum];
    }

    if (mus_playing == music)
    {
        return;
    }


    S_StopMusic();


    if (!music->lumpnum)
    {
        sprintf(namebuf, "d_%s", DEH_String(music->name));
        music->lumpnum = W_GetNumForName(namebuf);
    }

    music->data = W_CacheLumpNum(music->lumpnum, PU_STATIC);

    handle = I_RegisterSong(music->data, W_LumpLength(music->lumpnum));
    music->handle = handle;
    I_PlaySong(handle, looping);

    mus_playing = music;
}
