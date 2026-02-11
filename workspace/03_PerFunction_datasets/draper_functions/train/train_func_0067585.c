e2_option_sel_get (gchar *option)
{
	E2_OptionSet *set;
	set = e2_option_get (option);
	if (set != NULL && set->type == E2_OPTION_TYPE_SEL)
		return e2_option_sel_get_direct (set);
	return -1;
}
