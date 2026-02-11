savepath_command(char *arg, struct session *ses)
{
    if (ses!=nullsession)
    {
        get_arg_in_braces(arg, arg, 1);
        if (*arg)
        {
            char result[BUFFER_SIZE];
            struct listnode *ln = ses->path;
            int dirlen, len = 0;

            if (!ses->path_length)
            {
                tintin_eprintf(ses, "#No path to save!");
                return;
            }

            sprintf(result, "%calias {%s} {", tintin_char, arg);
            len = strlen(result);
            while ((ln = ln->next))
            {
                dirlen = strlen(ln->left);
                if (dirlen + len < BUFFER_SIZE - 10)
                {
                    strcat(result, ln->left);
                    len += dirlen + 1;
                    if (ln->next)
                        strcat(result, ";");
                }
                else
                {
                    tintin_eprintf(ses, "#Error - buffer too small to contain alias");
                    break;
                }
            }
            strcat(result, "}");
            parse_input(result,1,ses);
        }
        else
            tintin_eprintf(ses, "#Syntax: savepath <alias>");
    }
    else
        tintin_printf(ses,"#No session active => NO PATH TO SAVE!");
}
