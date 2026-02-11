desist_requested(void)
{
    int             result;

    result = desist_flag;
    desist_flag = 0;
    if (result != 0)
    {
        sub_context_ty  *scp;

        star_eoln();
        scp = sub_context_new();
        sub_var_set(scp, "Name", "%s", safe_strsignal(result));
        error_intl(scp, i18n("interrupted by $name"));
        sub_context_delete(scp);
    }
    return (result != 0);
}
