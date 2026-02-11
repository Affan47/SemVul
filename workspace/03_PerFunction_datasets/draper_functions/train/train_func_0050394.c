at_sms_delete_static(gn_data *data, struct gn_statemachine *state, int position)
{
	if (position < 1 || position > sizeof(sms_inbox)/sizeof(char *))
		return GN_ERR_INVALIDLOCATION;
	if (!sms_inbox[position - 1])
		return GN_ERR_EMPTYLOCATION;

	sms_inbox[position - 1] = NULL;

	return GN_ERR_NONE;
}
