e2_option_sel_register (gchar *name, gchar *group, gchar *desc,
	gchar *tip, gchar *depends, gint def, const gchar **values,
	E2_OptionFlags flags)
{
	E2_OptionSet *set = e2_option_register (E2_OPTION_TYPE_SEL, name, group,
		desc, tip, depends, flags);
	set->ex.sel.def = g_strdupv ((gchar **)values);
	gint i = 0;
	while (set->ex.sel.def[i++] != NULL);
	set->ex.sel.def_count = i - 1;

	set->hook_freezed = TRUE;
	e2_option_sel_set_direct (set, def);
	set->hook_freezed = FALSE;
	return set;
}
