ccss_style_set_property_selector_string (ccss_style_t		*self,
					 ccss_property_t const	*property,
					 char const		*selector)
{
#ifdef CCSS_DEBUG
	g_return_if_fail (self);
	g_return_if_fail (property);
	g_return_if_fail (selector);

	g_hash_table_insert (self->selectors, (gpointer) property, g_strdup (selector));
#endif
}
