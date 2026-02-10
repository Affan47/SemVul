sv_selection_copy (SheetView *sv, WorkbookControl *wbc)
{
	GnmRange const *sel;

	g_return_val_if_fail (IS_SHEET_VIEW (sv), FALSE);
	if (!(sel = selection_first_range (sv, GO_CMD_CONTEXT (wbc), _("Copy"))))
		return FALSE;

	gnm_app_clipboard_cut_copy (wbc, FALSE, sv, sel, TRUE);

	return TRUE;
}
