open_script_file(const char *fname, int quiet,
                                  int script_more_mode)
{
    int evt;
    char buf[50];


    osfildef *fp = osfoprt(fname, OSFTCMD);


    if (fp == 0)
        return;


    if (osfgets(buf, sizeof(buf), fp) != 0
        && strcmp(buf, "<eventscript>\n") == 0)
    {

        evt = TRUE;
    }
    else
    {


        evt = FALSE;
        osfseek(fp, 0, OSFSK_SET);
    }


    if (script_sp_ != 0)
    {


        if (script_sp_->quiet)
            quiet = TRUE;


        if (!script_sp_->more_mode)
            script_more_mode = FALSE;
    }


    script_sp_ = new script_stack_entry(
        script_sp_, set_more_state(script_more_mode), fp,
        script_more_mode, quiet, evt);


    if (!script_more_mode)
        os_nonstop_mode(TRUE);
}
