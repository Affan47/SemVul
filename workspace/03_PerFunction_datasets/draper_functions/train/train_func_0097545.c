status_misc(HSCPRC * hp, STRPTR s)
{
    if (disp_status_verbose)
    {
        strcpy(status_buf, "");
#if 0
        status_file_and_line(hp);
#endif
        strncat(status_buf, s, MAX_STATUSLEN - strlen(status_buf));
        status_msg(status_buf);
        status_lf();
    }
}
