option_tab_width_set(int n, void (*usage)(void))
{
    if (tab_width)
	duplicate_option_by_name(arglex_token_tab_width, usage);
    if (n < 0 || n > 40)
    {
	sub_context_ty *scp;

	scp = sub_context_new();
	sub_var_set_long(scp, "Number", n);
	error_intl(scp, i18n("tab width $number out of range"));
	sub_context_delete(scp);
	usage();
    }
    if (n < 2)
	tab_width = -1;
    else
	tab_width = n;
}
