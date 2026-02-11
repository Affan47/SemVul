BindSoundVariables(void)
{
    M_BindVariable("snd_sfxdevice",       &snd_sfxdevice);
    M_BindVariable("snd_musicdevice",     &snd_musicdevice);
    M_BindVariable("snd_channels",        &numChannels);
    M_BindVariable("sfx_volume",          &sfxVolume);
    M_BindVariable("music_volume",        &musicVolume);
    M_BindVariable("snd_samplerate",      &snd_samplerate);
    M_BindVariable("use_libsamplerate",   &use_libsamplerate);
    M_BindVariable("libsamplerate_scale", &libsamplerate_scale);
    M_BindVariable("timidity_cfg_path",   &timidity_cfg_path);
    M_BindVariable("gus_patch_path",      &gus_patch_path);
    M_BindVariable("gus_ram_kb",          &gus_ram_kb);

    M_BindVariable("snd_sbport",          &snd_sbport);
    M_BindVariable("snd_sbirq",           &snd_sbirq);
    M_BindVariable("snd_sbdma",           &snd_sbdma);
    M_BindVariable("snd_mport",           &snd_mport);

    M_BindVariable("snd_cachesize",       &snd_cachesize);
    M_BindVariable("opl_io_port",         &opl_io_port);

    if (gamemission == strife)
    {
        M_BindVariable("voice_volume",    &voiceVolume);
        M_BindVariable("show_talk",       &show_talk);
    }

    timidity_cfg_path = strdup("");
    gus_patch_path = strdup("");


#ifdef __MACOSX__
    {
        const SDL_version *v = Mix_Linked_Version();

        if (SDL_VERSIONNUM(v->major, v->minor, v->patch)
          < SDL_VERSIONNUM(1, 2, 11))
        {
            snd_musicdevice = SNDDEVICE_NONE;
        }
    }
#endif
}
