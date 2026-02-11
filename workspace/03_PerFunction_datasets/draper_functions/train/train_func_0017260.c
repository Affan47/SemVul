status_msg(STRPTR s)
{
    size_t new_stmsg_len = strlen(s);
    size_t i;

    if (disp_status)
    {

        if (s[0])
            fputs(s, stderr);


        for (i = new_stmsg_len; i < prev_stmsg_len; i++)
            fputs(" ", stderr);


        fputs("\r", stderr);
        fflush(stderr);

        prev_stmsg_len = new_stmsg_len;
    }
}
