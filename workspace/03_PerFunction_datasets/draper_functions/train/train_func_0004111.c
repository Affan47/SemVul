ConfigSound(void)
{
    txt_window_t *window;
    txt_table_t *sfx_table;
    txt_table_t *music_table;
    txt_table_t *extra_table;
    txt_dropdown_list_t *sfx_mode_control;
    txt_dropdown_list_t *music_mode_control;
    int num_sfx_modes, num_music_modes;


    if (snd_sfxdevice == SNDDEVICE_PCSPEAKER)
    {
        snd_sfxmode = SFXMODE_PCSPEAKER;
    }
    else if (snd_sfxdevice >= SNDDEVICE_SB)
    {
        snd_sfxmode = SFXMODE_DIGITAL;
    }
    else
    {
        snd_sfxmode = SFXMODE_DISABLED;
    }


    switch (snd_musicdevice)
    {
        case SNDDEVICE_GENMIDI:
            snd_musicmode = MUSICMODE_NATIVE;
            break;
        case SNDDEVICE_CD:
            snd_musicmode = MUSICMODE_CD;
            break;
        case SNDDEVICE_SB:
        case SNDDEVICE_ADLIB:
        case SNDDEVICE_AWE32:
            snd_musicmode = MUSICMODE_OPL;
            break;
        case SNDDEVICE_GUS:
            snd_musicmode = MUSICMODE_GUS;
            break;
        default:
            snd_musicmode = MUSICMODE_DISABLED;
            break;
    }


    if (gamemission == doom)
    {
        num_sfx_modes = NUM_SFXMODES;
    }
    else
    {
        num_sfx_modes = NUM_SFXMODES - 1;
    }


    if (gamemission == hexen)
    {
        num_music_modes = NUM_MUSICMODES;
    }
    else
    {
        num_music_modes = NUM_MUSICMODES - 1;
    }


    window = TXT_NewWindow("Sound configuration");

    TXT_SetWindowPosition(window, TXT_HORIZ_CENTER, TXT_VERT_TOP,
                                  TXT_SCREEN_W / 2, 6);

    TXT_AddWidgets(window,
               TXT_NewSeparator("Sound effects"),
               sfx_table = TXT_NewTable(2),
               NULL);

    TXT_SetColumnWidths(sfx_table, 20, 14);

    TXT_AddWidgets(sfx_table,
                   TXT_NewLabel("Sound effects"),
                   sfx_mode_control = TXT_NewDropdownList(&snd_sfxmode,
                                                          sfxmode_strings,
                                                          num_sfx_modes),
                   TXT_NewLabel("Sound channels"),
                   TXT_NewSpinControl(&numChannels, 1, 8),
                   TXT_NewLabel("SFX volume"),
                   TXT_NewSpinControl(&sfxVolume, 0, 15),
                   NULL);

    if (gamemission == strife)
    {
        TXT_AddWidgets(sfx_table,
                       TXT_NewLabel("Voice volume"),
                       TXT_NewSpinControl(&voiceVolume, 0, 15),
                       NULL);
        TXT_AddWidget(window,
                      TXT_NewCheckBox("Show text with voices", &show_talk));
    }

    TXT_AddWidgets(window,
               TXT_NewSeparator("Music"),
               music_table = TXT_NewTable(2),
               extra_table = TXT_NewTable(1),
               NULL);

    TXT_SetColumnWidths(music_table, 20, 14);

    TXT_AddWidgets(music_table,
                   TXT_NewLabel("Music"),
                   music_mode_control = TXT_NewDropdownList(&snd_musicmode,
                                                            musicmode_strings,
                                                            num_music_modes),
                   TXT_NewLabel("Music volume"),
                   TXT_NewSpinControl(&musicVolume, 0, 15),
                   NULL);


    TXT_SignalConnect(sfx_mode_control, "changed", UpdateSndDevices, NULL);
    TXT_SignalConnect(music_mode_control, "changed", UpdateSndDevices, NULL);


    TXT_SignalConnect(music_mode_control, "changed",
                      UpdateExtraTable, extra_table);
    UpdateExtraTable(music_mode_control, extra_table);
}
