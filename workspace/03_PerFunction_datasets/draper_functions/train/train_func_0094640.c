_constructWindow(void)
{
	const XAP_StringSet * pSS = m_pApp->getStringSet();


#if GTK_CHECK_VERSION(3,0,0)
	GtkBuilder* builder = newDialogBuilder("ap_UnixDialog_MailMerge.ui");
#else
	GtkBuilder* builder = newDialogBuilder("ap_UnixDialog_MailMerge-2.ui");
#endif


	m_windowMain = GTK_WIDGET(gtk_builder_get_object(builder, "ap_UnixDialog_MailMerge"));
	m_entry = GTK_WIDGET(gtk_builder_get_object(builder, "edFieldName"));
	m_treeview = GTK_WIDGET(gtk_builder_get_object(builder, "tvAvailableFields"));


    gtk_tree_selection_set_mode (gtk_tree_view_get_selection (GTK_TREE_VIEW (m_treeview)), GTK_SELECTION_SINGLE);


	std::string s;
	pSS->getValueUTF8(AP_STRING_ID_DLG_MailMerge_MailMergeTitle,s);
	abiDialogSetTitle(m_windowMain, "%s", s.c_str());


	localizeLabelMarkup(GTK_WIDGET(gtk_builder_get_object(builder, "lbAvailableFields")), pSS, AP_STRING_ID_DLG_MailMerge_AvailableFields);

	localizeLabelMarkup(GTK_WIDGET(gtk_builder_get_object(builder, "lbFieldName")), pSS, AP_STRING_ID_DLG_MailMerge_Insert);

	localizeLabel(GTK_WIDGET(gtk_builder_get_object(builder, "lbOpenFile")), pSS, AP_STRING_ID_DLG_MailMerge_OpenFile);

	localizeButtonUnderline(GTK_WIDGET(gtk_builder_get_object(builder, "btInsert")), pSS, AP_STRING_ID_DLG_InsertButton);

	g_signal_connect_after(G_OBJECT(m_treeview),
						   "cursor-changed",
						   G_CALLBACK(s_types_clicked),
						   static_cast<gpointer>(this));
	g_signal_connect_after(G_OBJECT(m_treeview),
						   "row-activated",
						   G_CALLBACK(s_types_dblclicked),
						   static_cast<gpointer>(this));

	g_signal_connect(G_OBJECT(m_windowMain), "response",
					 G_CALLBACK(s_response_triggered), this);


	g_signal_connect(G_OBJECT(m_windowMain),
			   "destroy",
			   G_CALLBACK(s_destroy_clicked),
			   (gpointer) this);
	g_signal_connect(G_OBJECT(m_windowMain),
			   "delete_event",
			   G_CALLBACK(s_delete_clicked),
			   (gpointer) this);

	g_object_unref(G_OBJECT(builder));

	return m_windowMain;
}
