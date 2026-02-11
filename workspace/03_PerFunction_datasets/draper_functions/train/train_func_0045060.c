document_highlight_tags(GeanyDocument *doc)
{
	GString *keywords_str;
	gchar *keywords;
	gint keyword_idx;


	switch (doc->file_type->id)
	{
		case GEANY_FILETYPES_C:
		case GEANY_FILETYPES_CPP:
		case GEANY_FILETYPES_CS:
		case GEANY_FILETYPES_D:
		case GEANY_FILETYPES_JAVA:
		case GEANY_FILETYPES_OBJECTIVEC:
		case GEANY_FILETYPES_VALA:
		{


			keyword_idx = 3;
			break;
		}
		default:
			return;
	}
	if (!app->tm_workspace->work_object.tags_array)
		return;


	keywords_str = symbols_find_tags_as_string(app->tm_workspace->work_object.tags_array,
		TM_GLOBAL_TYPE_MASK, doc->file_type->lang);
	if (keywords_str)
	{
		keywords = g_string_free(keywords_str, FALSE);
		sci_set_keywords(doc->editor->sci, keyword_idx, keywords);
		g_free(keywords);
		queue_colourise(doc);
	}
}
