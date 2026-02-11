appearance_convert (ccss_cairo_appearance_t const		*property,
		    ccss_property_type_t	 target,
		    void			*value)
{
	char *ret;

	g_return_val_if_fail (property && value, false);

	if (CCSS_PROPERTY_TYPE_DOUBLE == target)
		return false;

	if (property->module) {
		ret = g_strdup_printf ("%s \"%s\"",
				       property->appearance,
				       property->module->module_path);

	} else {
		ret = g_strdup (property->appearance);
	}

	* (char **) value = ret;

	return true;
}
