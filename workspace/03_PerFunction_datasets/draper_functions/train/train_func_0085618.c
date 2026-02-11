getitem_command(char *arg,struct session *ses)
{
    char destvar[BUFFER_SIZE], itemnrtxt[BUFFER_SIZE],
    list[BUFFER_SIZE], temp1[BUFFER_SIZE];
    int  i, itemnr;

    arg = get_arg(arg, destvar, 0, ses);
    arg = get_arg(arg, itemnrtxt, 0, ses);

    if (!*destvar || !*itemnrtxt)
    {
        tintin_eprintf(ses,"#Error - Syntax: #getitem {destination variable} {item number} {list}");
    }
    else
    {
        if (sscanf(itemnrtxt,"%d",&itemnr) != 1)
            tintin_eprintf(ses,"#Error in #getitem - expected a _number_ as item number, got {%s}.",itemnrtxt);
        else
        {
            get_arg(arg, list, 1, ses);
            arg = list;
            i=0;
            if (itemnr>0)
            {
                do {
                    arg = get_arg_in_braces(arg, temp1, 0);
                    i++;
                } while (i!=itemnr);

                if (*temp1)
                    set_variable(destvar,temp1,ses);
                else
                {
                    set_variable(destvar,"",ses);
                    if (ses->mesvar[5])
                        tintin_printf(ses,"#Item doesn't exist!");
                }
            }
        }
    }
}
