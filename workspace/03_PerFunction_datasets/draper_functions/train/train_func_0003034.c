on_window_key_press(GtkWidget * window, GdkEventKey * event ,CDict * parent)
{
	gboolean return_val=true;
	const char* text;
	switch (event->keyval)
	{
		case GDK_Escape:
			text = gtk_entry_get_text(GTK_ENTRY(parent->word_entry));
			if (text && text[0]!='\0')
			{
				gtk_entry_set_text(GTK_ENTRY(parent->word_entry),"");
			}
			else
			{
				parent->exit_button.do_clicked();
			}
			break;
		default:
			return_val=false;
	}
	return return_val;
}
