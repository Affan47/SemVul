system_command(char *arg,struct session *ses)
{
    FILE *output;
    char buf[BUFFER_SIZE],ustr[BUFFER_SIZE];
    mbstate_t cs;

    get_arg(arg, arg, 1, ses);
    if (*arg)
    {
        if (ses->mesvar[9])
            tintin_puts1("#EXECUTING SHELL COMMAND.", ses);
        utf8_to_local(buf, arg);
        if (!(output = mypopen(buf,0)))
        {
            tintin_puts1("#ERROR EXECUTING SHELL COMMAND.",ses);
            prompt(NULL);
            return;
        };
        memset(&cs, 0, sizeof(cs));

        while (fgets(buf,BUFFER_SIZE,output))
        {
            do_in_MUD_colors(buf,1);
            local_to_utf8(ustr, buf, BUFFER_SIZE, &cs);
            user_textout(ustr);
        }
        fclose(output);
        if (ses->mesvar[9])
            tintin_puts1("#OK COMMAND EXECUTED.", ses);
    }
    else
        tintin_eprintf(ses,"#EXECUTE WHAT COMMAND?");
    prompt(NULL);

}
