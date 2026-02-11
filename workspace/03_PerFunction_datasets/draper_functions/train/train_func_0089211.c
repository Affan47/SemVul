get_context_flags (ParserState *parser_state)
{
	guint i;
	xmlChar *value;
	GtkSourceContextFlags flags = GTK_SOURCE_CONTEXT_EXTEND_PARENT;
	const gchar *names[] = {
		"extend-parent", "end-parent", "end-at-line-end",
		"first-line-only", "once-only", "style-inside"
	};
	GtkSourceContextFlags values[] = {
		GTK_SOURCE_CONTEXT_EXTEND_PARENT,
		GTK_SOURCE_CONTEXT_END_PARENT,
		GTK_SOURCE_CONTEXT_END_AT_LINE_END,
		GTK_SOURCE_CONTEXT_FIRST_LINE_ONLY,
		GTK_SOURCE_CONTEXT_ONCE_ONLY,
		GTK_SOURCE_CONTEXT_STYLE_INSIDE
	};

	g_assert (G_N_ELEMENTS (names) == G_N_ELEMENTS (values));

	for (i = 0; i < G_N_ELEMENTS (names); ++i)
	{
		value = xmlTextReaderGetAttribute (parser_state->reader, BAD_CAST names[i]);

		if (value != NULL)
		{
			if (str_to_bool (value))
				flags |= values[i];
			else
				flags &= ~values[i];
		}

		xmlFree (value);
	}

	return flags;
}
