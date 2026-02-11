border_style_convert (ccss_border_style_t const	*property,
		      ccss_property_type_t	 target,
		      void			*value)
{
	g_return_val_if_fail (property && value, false);

	if (CCSS_PROPERTY_TYPE_DOUBLE == target)
		return false;

	* (char **) value = g_strdup (lookup_style (property->style));

	return true;
}
