gnm_app_clipboard_sheet_get (void)
{
	g_return_val_if_fail (app != NULL, NULL);

	if (app->clipboard_sheet_view == NULL)
		return NULL;
	return sv_sheet (app->clipboard_sheet_view);
}
