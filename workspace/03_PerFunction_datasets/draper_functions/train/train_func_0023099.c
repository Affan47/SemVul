sheet_scrollbar_config (Sheet const *sheet)
{
	g_return_if_fail (IS_SHEET (sheet));

	SHEET_FOREACH_CONTROL (sheet, view, control,
		sc_scrollbar_config (control););
}
