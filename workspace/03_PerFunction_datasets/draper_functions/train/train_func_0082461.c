AP_UnixDialog_Goto__onSwitchPage (GtkNotebook *notebook,
											  gpointer Page,
											  guint page,
											  gpointer data)
{
	UT_UNUSED(notebook);
	UT_UNUSED(Page);
	UT_DEBUGMSG(("_onSwitchPage() '%d'\n", page));

	if (page == 0)
	{
		AP_UnixDialog_Goto *dlg = static_cast<AP_UnixDialog_Goto *>(data);
		dlg->updatePosition();
	}
}
