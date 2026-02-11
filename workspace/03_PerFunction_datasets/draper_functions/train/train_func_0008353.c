arglex(void)
{
    arglex_table_ty *tp;
    int             j;
    arglex_table_ty *hit[20];
    int             nhit;
    char            *arg;
    static char     *pushback[3];
    static int      pushback_depth;

    trace(("arglex()\n{\n"));
    if (pushback_depth)
    {


        arg = pushback[--pushback_depth];
    }
    else
    {
        if (argc <= 0)
        {
            arglex_token = arglex_token_eoln;
            arg = "";
            goto done;
        }
        arg = argv[0];
        argc--;
        argv++;


        if (arg[0] == '-' && arg[1] != '=')
        {
            char           *eqp;

            eqp = strchr(arg, '=');
            if (eqp)
            {
                pushback[pushback_depth++] = eqp + 1;
                *eqp = 0;
            }
        }


        if (arg[0] == '-' && arg[1] == '-' && arg[2] && !is_a_number(arg + 1))
            ++arg;
    }


    if (is_a_number(arg))
    {
        arglex_token = arglex_token_number;
        goto done;
    }


    nhit = 0;
    partial = 0;
    for (tp = table; tp < ENDOF(table); tp++)
    {
        if (arglex_compare(tp->name, arg))
            hit[nhit++] = tp;
    }
    if (utable)
    {
        for (tp = utable; tp->name; tp++)
        {
            if (arglex_compare(tp->name, arg))
                hit[nhit++] = tp;
        }
    }


    switch (nhit)
    {
    case 0:


        if (*arg == '-')
            arglex_token = arglex_token_option;
        else
            arglex_token = arglex_token_string;
        break;

    case 1:
        if (partial)
            pushback[pushback_depth++] = (char *)partial;
        arg = hit[0]->name;
        arglex_token = hit[0]->token;
        break;

    default:
    {
        string_ty      *s1;
        string_ty      *s2;
        sub_context_ty *scp;

        s1 = str_from_c(hit[0]->name);
        for (j = 1; j < nhit; ++j)
        {
            s2 = str_format("%s, %s", s1->str_text, hit[j]->name);
            str_free(s1);
            s1 = s2;
        }
        scp = sub_context_new();
        sub_var_set_charstar(scp, "Name", arg);
        sub_var_set_string(scp, "Guess", s1);
        fatal_intl(scp, i18n("option \"$name\" ambiguous ($guess)"));

    }
    }


  done:
    arglex_value.alv_string = arg;
    trace(("return %d; /* \"%s\" */\n", arglex_token, arg));
    trace(("}\n"));
    return arglex_token;
}
