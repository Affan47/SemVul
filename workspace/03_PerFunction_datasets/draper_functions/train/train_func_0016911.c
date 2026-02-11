Mac_Header_Read_File_Info(gchar *filename, ET_File_Info *ETFileInfo)
{
    StreamInfoMac Info;

    if (info_mac_read(filename, &Info))
    {
        gchar *filename_utf8 = filename_to_display(filename);
        fprintf(stderr,"MAC header not found for file '%s'\n", filename_utf8);
        g_free(filename_utf8);
        return FALSE;
    }
    ETFileInfo->mpc_profile   = g_strdup(Info.CompresionName);
    ETFileInfo->version       = Info.Version;
    ETFileInfo->bitrate       = Info.Bitrate/1000.0;
    ETFileInfo->samplerate    = Info.SampleFreq;
    ETFileInfo->mode          = Info.Channels;
    ETFileInfo->size          = Info.FileSize;
    ETFileInfo->duration      = Info.Duration/1000;

    return TRUE;
}
