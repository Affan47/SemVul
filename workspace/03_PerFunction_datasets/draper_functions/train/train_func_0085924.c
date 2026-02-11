gnc_file_open_file (const char * newfile, gboolean open_readonly)
{
    if (!newfile) return FALSE;

    if (!gnc_file_query_save (TRUE))
        return FALSE;

    return gnc_post_file_open (newfile, open_readonly);
}
