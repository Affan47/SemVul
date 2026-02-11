dmi_matched(const struct dmi_system_id *dmi)
{
	char *model;

	quirks = dmi->driver_data;

	model = (char *)dmi->matches[1].substr;
	if (unlikely(strncmp(model, "ET2012", 6) == 0))
		et2012_quirks();

	return 1;
}
