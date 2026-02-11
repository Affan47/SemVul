gnc_xml_be_backup_file(FileBackend *be)
{
    gboolean bkup_ret;
    char *timestamp;
    char *backup;
    const char *datafile;
    struct stat statbuf;
    int rc;

    datafile = be->fullpath;

    rc = g_stat (datafile, &statbuf);
    if (rc)
        return (errno == ENOENT);

    if (gnc_xml_be_determine_file_type(datafile) == GNC_BOOK_BIN_FILE)
    {

        const char *back = "-binfmt.bkup";
        char *bin_bkup = g_new(char, strlen(datafile) + strlen(back) + 1);
        strcpy(bin_bkup, datafile);
        strcat(bin_bkup, back);
        bkup_ret = gnc_int_link_or_make_backup(be, datafile, bin_bkup);
        g_free(bin_bkup);
        if (!bkup_ret)
        {
            return FALSE;
        }
    }

    timestamp = gnc_date_timestamp ();
    backup = g_strconcat( datafile, ".", timestamp, GNC_DATAFILE_EXT, NULL );
    g_free (timestamp);

    bkup_ret = gnc_int_link_or_make_backup(be, datafile, backup);
    g_free(backup);

    return bkup_ret;
}
