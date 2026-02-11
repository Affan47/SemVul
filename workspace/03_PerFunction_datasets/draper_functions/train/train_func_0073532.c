e2_option_bool_set_direct (E2_OptionSet *set, gboolean value)
{
	set->ival = value;
	set->sval = (value) ? "true" : "false";
	if (!set->hook_freezed)
		e2_hook_list_run (&set->hook_value_changed, GINT_TO_POINTER (value));
	return value;
}
