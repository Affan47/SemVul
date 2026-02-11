clipboard_copy_range_undo (Sheet *sheet, GnmRange const *r)
{
	GnmCellRegion *cr = clipboard_copy_range (sheet, r);
	g_return_val_if_fail (cr != NULL, NULL);
	return go_undo_binary_new (cr, gnm_sheet_range_new (sheet, r),
				   (GOUndoBinaryFunc)cb_clipboard_copy_range_undo,
				   (GFreeFunc)cellregion_unref,
				   (GFreeFunc)g_free);
}
