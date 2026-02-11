read_named_style(const gchar *named_style, GeanyLexerStyle *style)
{
	GeanyLexerStyle *cs;
	gchar *comma, *name = NULL;
	const gchar *bold = NULL;
	const gchar *italic = NULL;

	g_return_val_if_fail(named_style, FALSE);
	name = utils_strdupa(named_style);

	comma = strstr(name, ",");
	if (comma)
	{
		bold = strstr(comma, ",bold");
		italic = strstr(comma, ",italic");
		*comma = '\0';
	}
	cs = g_hash_table_lookup(named_style_hash, name);

	if (cs)
	{
 		*style = *cs;
 		if (bold)
 			style->bold = !style->bold;
 		if (italic)
 			style->italic = !style->italic;
	}
	else
	{
		*style = gsd_default;
	}
	return (cs != NULL);
}
