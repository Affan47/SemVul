xxxgtk_textview_set_text (GtkTextView *text, const char *str)
{
    GtkTextBuffer *buff = gtk_text_view_get_buffer (text);
    if (!str) str = "";
    gtk_text_buffer_set_text (buff, str, strlen (str));

}
