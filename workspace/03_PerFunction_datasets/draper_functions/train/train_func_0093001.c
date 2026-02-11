gnm_filter_new (Sheet *sheet, GnmRange const *r)
{
	GnmFilter	*filter;

	g_return_val_if_fail (IS_SHEET (sheet), NULL);
	g_return_val_if_fail (r != NULL, NULL);

	filter = g_new0 (GnmFilter, 1);

	filter->is_active = FALSE;
	filter->r = *r;
	filter->fields = g_ptr_array_new ();


	gnm_filter_attach (filter, sheet);

	return filter;
}
