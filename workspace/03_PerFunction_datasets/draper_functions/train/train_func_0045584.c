emit_open(char *s)
{
    sub_context_ty  *scp;

    trace(("open\n"));
    assert(!output);
    if (s)
    {
        output = fopen_and_check(s, "w");
        filename = str_from_c(s);
    }
    else
    {
        scp = sub_context_new();
        filename = subst_intl(scp, i18n("standard output"));
        sub_context_delete(scp);
        output = stdout;
    }
    icol = 0;
    ocol = 0;
    back_slash_seen = 0;
}
