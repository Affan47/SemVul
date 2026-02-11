localizeLabelUnderline(GtkWidget * widget, const XAP_StringSet * pSS, XAP_String_Id id)
{
	std::string s;
	pSS->getValueUTF8(id,s);
	gchar * newlbl = g_strdup(s.c_str());
	UT_ASSERT(newlbl);
	convertMnemonics(newlbl);
	gtk_label_set_text_with_mnemonic (GTK_LABEL(widget), newlbl);
	FREEP(newlbl);
}
