s_select_image(GtkWidget *widget, gpointer data)
{
	AP_UnixDialog_FormatTable * dlg = reinterpret_cast<AP_UnixDialog_FormatTable *>(data);
	UT_return_val_if_fail(widget && dlg, FALSE);
	dlg->askForGraphicPathName();
	return FALSE;
}
