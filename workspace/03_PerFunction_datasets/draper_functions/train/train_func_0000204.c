page_width_set(int n)
{
    sub_context_ty  *scp;

    if (page_width)
    {
        arg_duplicate(arglex_token_page_width, 0);

    }
    if (n < MIN_PAGE_WIDTH || n > MAX_PAGE_WIDTH)
    {
        scp = sub_context_new();
        sub_var_set(scp, "Number", "%d", n);
        fatal_intl(scp, i18n("page width $number out of range"));

    }
    page_width = n;
}
