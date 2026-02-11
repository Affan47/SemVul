options_parse_keyword(GQParserData *parser_data, GMarkupParseContext *context, const gchar *element_name, const gchar **attribute_names, const gchar **attribute_values, gpointer data, GError **error)
{
	GtkTreeIter *iter_ptr = data;
	if (g_ascii_strcasecmp(element_name, "keyword") == 0)
		{
		GtkTreeIter *child = keyword_add_from_config(keyword_tree, iter_ptr, attribute_names, attribute_values);
		options_parse_func_push(parser_data, options_parse_keyword, options_parse_keyword_end, child);
		}
	else
		{
		log_printf("unexpected in <keyword>: <%s>\n", element_name);
		options_parse_func_push(parser_data, options_parse_leaf, NULL, NULL);
		}
}
