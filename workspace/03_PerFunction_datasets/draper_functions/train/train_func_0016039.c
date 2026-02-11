print()
    const
{
    sub_context_ty sc;
    sc.var_set_string("MeSsaGe", what);
    if (where)
        where->print_error(sc, i18n("$message"));
    else
        sc.error_intl(i18n("$message"));
}
