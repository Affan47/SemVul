inputkey(VMG_ uint argc)
{
    char buf[32];
    char c[10];
    size_t len;
    int evt;
    static const int filter[] = { OS_EVT_KEY };


    check_argc(vmg_ argc, 0);


    if (G_console->read_event_script(
        vmg_ &evt, buf, sizeof(buf),
        filter, sizeof(filter)/sizeof(filter[0]), 0))
    {

        retval_ui_str(vmg_ buf);


        G_console->log_event(vmg_ OS_EVT_KEY, buf, strlen(buf), FALSE);


        return;
    }


    G_console->flush_all(vmg_ VM_NL_INPUT);


    c[0] = (char)os_getc_raw();
    len = 1;


    if (c[0] == 0)
    {
        char extc;


        extc = (char)os_getc_raw();


        map_ext_key(vmg_ buf, (unsigned char)extc);
    }
    else
    {

        while (!raw_key_complete(vmg_ c, len) && len + 1 < sizeof(c))
        {


            c[len++] = (char)os_getc_raw();
        }
        c[len] = '\0';


        map_raw_key(vmg_ buf, c, len);
    }


    G_console->reset_line_count(FALSE);


    G_console->log_event(vmg_ OS_EVT_KEY, buf, strlen(buf), TRUE);


    retval_str(vmg_ buf);
}
