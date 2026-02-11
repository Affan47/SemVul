symbols_find_tags_as_string(GPtrArray *tags_array, guint tag_types, gint lang)
{
	guint j;
	TMTag *tag;
	GString *s = NULL;
	GPtrArray *typedefs;
	gint tag_lang;

	g_return_val_if_fail(tags_array != NULL, NULL);

	typedefs = tm_tags_extract(tags_array, tag_types);

	if ((typedefs) && (typedefs->len > 0))
	{
		s = g_string_sized_new(typedefs->len * 10);
		for (j = 0; j < typedefs->len; ++j)
		{
			tag = TM_TAG(typedefs->pdata[j]);


			tag_lang = (tag->atts.entry.file) ? tag->atts.entry.file->lang : tag->atts.file.lang;


			if (tag->name && (tag_lang == lang || lang == -2))
			{
				if (j != 0)
					g_string_append_c(s, ' ');
				g_string_append(s, tag->name);
			}
		}
	}
	if (typedefs)
		g_ptr_array_free(typedefs, TRUE);
	return s;
}
