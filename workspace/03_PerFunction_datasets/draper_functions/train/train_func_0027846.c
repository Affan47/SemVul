OnGetData (GtkClipboard *clipboard, GtkSelectionData *selection_data,  guint info)
{
	xmlDocPtr pDoc = gcp::WidgetData::GetXmlDoc (clipboard);
	guint *DataType = (clipboard == gtk_clipboard_get (GDK_SELECTION_CLIPBOARD))? &gcp::ClipboardDataType: &gcp::ClipboardDataType1;
	*DataType = info;
	gint size;
	if (info) {
		if (gcp::ClipboardTextData) {
			g_free (gcp::ClipboardTextData);
		}
		gcp::Text *text = new gcp::Text ();
		text->Load (pDoc->children->children);
		gcp::ClipboardTextData = g_strdup (text->GetBuffer ().c_str ());
		delete text;
		size = strlen ((char*) gcp::ClipboardTextData);
		gtk_selection_data_set_text (selection_data, (const gchar*) gcp::ClipboardTextData, size);
	} else {
		xmlDocDumpFormatMemory (pDoc, &gcp::ClipboardData, &size, info);
		gtk_selection_data_set (selection_data, gdk_atom_intern (GCHEMPAINT_ATOM_NAME, FALSE), 8,  (const guchar*) gcp::ClipboardData, size);
	}
	if (clipboard == gtk_clipboard_get (GDK_SELECTION_CLIPBOARD))
			static_cast < gcp::Window * > (m_pView->GetDoc ()->GetWindow ())->ActivateActionWidget ("/MainMenu/EditMenu/Paste", true);
}
