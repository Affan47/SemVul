write_start_end_tag_with_content_as_list (GOutputStream *os,
                                          const gchar *tag_name,
                                          GList *content_list)
{
	GList *iter = NULL;
	GString *content = g_string_new ("");
	gchar *cur_word = NULL;

	for (iter = g_list_first (content_list); iter != NULL; iter = g_list_next (iter))
	{
		cur_word = (gchar *)iter->data;
		g_string_append (content, cur_word);
		g_string_append (content, " ");
	}

	write_start_end_tag_with_content (os, tag_name, content->str);
	g_string_free (content, TRUE);

}
