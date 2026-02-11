dom_chars_handler(
    GSList *sibling_data, gpointer parent_data, gpointer global_data,
    gpointer *result, const char *text, int length)
{
    if (length > 0)
    {
	gchar *newtext = g_strdup (text);
        xmlNodeAddContentLen((xmlNodePtr)parent_data,
			     checked_char_cast (newtext), length);
	g_free (newtext);
    }
    return TRUE;
}
