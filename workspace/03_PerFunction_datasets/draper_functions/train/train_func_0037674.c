setWrap(bool vl)
{
	if (vl)
		gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(textview), GTK_WRAP_WORD_CHAR);
	else
		gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(textview), GTK_WRAP_NONE);
}
