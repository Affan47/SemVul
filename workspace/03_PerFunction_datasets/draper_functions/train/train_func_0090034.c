_populateWindowData(GtkBuilder* builder)
{
    const XAP_StringSet * pSS = m_pApp->getStringSet();
    std::string text;
	localizeLabelMarkup (GTK_WIDGET(gtk_builder_get_object(builder, "lbDocCompared")), pSS, XAP_STRING_ID_DLG_DocComparison_DocsCompared);
	gtk_label_set_text (GTK_LABEL(gtk_builder_get_object(builder, "lbDocument1")), getPath1());
	gtk_label_set_text (GTK_LABEL(gtk_builder_get_object(builder, "lbDocument2")), getPath2());
	localizeLabelMarkup (GTK_WIDGET(gtk_builder_get_object(builder, "lbResults")), pSS, XAP_STRING_ID_DLG_DocComparison_Results);
	pSS->getValueUTF8(XAP_STRING_ID_DLG_DocComparison_Relationship, text);
	gtk_label_set_text (GTK_LABEL(gtk_builder_get_object(builder, "lbRelationship")), text.c_str());
	gtk_label_set_text (GTK_LABEL(gtk_builder_get_object(builder, "lbRelationshipRes")), getResultValue(0));
	pSS->getValueUTF8(XAP_STRING_ID_DLG_DocComparison_Content, text);
	gtk_label_set_text (GTK_LABEL(gtk_builder_get_object(builder, "lbContent")), text.c_str());
	gtk_label_set_text (GTK_LABEL(gtk_builder_get_object(builder, "lbContentRes")), getResultValue(1));
	pSS->getValueUTF8(XAP_STRING_ID_DLG_DocComparison_Fmt, text);
	gtk_label_set_text (GTK_LABEL(gtk_builder_get_object(builder, "lbFormat")), text.c_str());
	gtk_label_set_text (GTK_LABEL(gtk_builder_get_object(builder, "lbFormatRes")), getResultValue(2));
	pSS->getValueUTF8(XAP_STRING_ID_DLG_DocComparison_Styles, text);
	gtk_label_set_text (GTK_LABEL(gtk_builder_get_object(builder, "lbStyles")), text.c_str());
	gtk_label_set_text (GTK_LABEL(gtk_builder_get_object(builder, "lbStylesRes")),getResultValue(3));
}
