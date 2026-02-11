debuglog_command(char *arg, struct session *ses)
{
    char fname[BUFFER_SIZE], temp[BUFFER_SIZE];

    if (*arg)
    {
        if (ses->debuglogfile)
        {
            fclose(ses->debuglogfile);
            if (ses->mesvar[MSG_LOG])
                tintin_printf(ses, "#OK. DEBUGLOG TURNED OFF.");
            ses->debuglogfile = NULL;
            SFREE(ses->debuglogname);
            ses->debuglogname = NULL;
        }
        get_arg_in_braces(arg, temp, 1);
        substitute_vars(temp, fname);
        substitute_myvars(fname, temp, ses);
            ses->debuglogfile=open_logfile(ses,temp,
                "#OK. DEBUGLOG SET TO {%s} .....",
                "#OK. DEBUGLOG APPENDING TO {%s} .....",
                "#OK. DEBUGLOG PIPED TO {%s} .....");
        if (ses->debuglogfile)
            ses->debuglogname=mystrdup(temp);
    }
    else if (ses->debuglogfile)
    {
        fclose(ses->debuglogfile);
        ses->debuglogfile = NULL;
        SFREE(ses->debuglogname);
        ses->debuglogname = NULL;
        if (ses->mesvar[MSG_LOG])
            tintin_printf(ses, "#OK. DEBUGLOG TURNED OFF.");
    }
    else
        tintin_printf(ses, "#DEBUGLOG ALREADY OFF.");
    prompt(NULL);
}
