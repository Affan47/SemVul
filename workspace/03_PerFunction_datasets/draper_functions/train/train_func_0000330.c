UpdateExtraTable(TXT_UNCAST_ARG(widget),
                             TXT_UNCAST_ARG(extra_table))
{
    TXT_CAST_ARG(txt_table_t, extra_table);


    TXT_ClearTable(extra_table);

    if (snd_musicmode == MUSICMODE_GUS)
    {
        TXT_AddWidgets(extra_table,
                       TXT_NewLabel("GUS patch path:"),
                       TXT_NewFileSelector(&gus_patch_path, 30,
                                           "Select path to GUS patches",
                                           TXT_DIRECTORY),
                       NULL);
    }

    if (snd_musicmode == MUSICMODE_NATIVE)
    {
        TXT_AddWidgets(extra_table,
                       TXT_NewLabel("Timidity configuration file:"),
                       TXT_NewFileSelector(&timidity_cfg_path, 30,
                                           "Select Timidity config file",
                                           cfg_extension),
                       NULL);
    }
}
