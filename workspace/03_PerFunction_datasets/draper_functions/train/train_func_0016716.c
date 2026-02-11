sys_check_eqn_list (const int *list)
{
    int dupv = gretl_list_duplicates(list, EQUATION);

    if (dupv >= 0) {
	gretl_errmsg_sprintf(_("variable %d duplicated in the "
			       "command list."), dupv);
	return E_DATA;
    } else {
	return 0;
    }
}
