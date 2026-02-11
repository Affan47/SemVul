options_parse_layout(GQParserData *parser_data, GMarkupParseContext *context, const gchar *element_name, const gchar **attribute_names, const gchar **attribute_values, gpointer data, GError **error)
{
	LayoutWindow *lw = data;
	if (g_ascii_strcasecmp(element_name, "bar") == 0)
		{
		if (!lw->bar)
			{
			GtkWidget *bar = bar_new_from_config(lw, attribute_names, attribute_values);
			layout_bar_set(lw, bar);
			}
		else
			{
			bar_update_from_config(lw->bar, attribute_names, attribute_values);
			}

		options_parse_func_push(parser_data, options_parse_bar, NULL, lw->bar);
		}
	else if (g_ascii_strcasecmp(element_name, "bar_sort") == 0)
		{
		GtkWidget *bar = bar_sort_new_from_config(lw, attribute_names, attribute_values);
		layout_bar_sort_set(lw, bar);
		options_parse_func_push(parser_data, options_parse_leaf, NULL, NULL);
		}
	else if (g_ascii_strcasecmp(element_name, "toolbar") == 0)
		{
		options_parse_func_push(parser_data, options_parse_toolbar, NULL, lw);
		}
	else if (g_ascii_strcasecmp(element_name, "statusbar") == 0)
		{
		options_parse_func_push(parser_data, options_parse_statusbar, NULL, lw);
		}
	else
		{
		log_printf("unexpected in <layout>: <%s>\n", element_name);
		options_parse_func_push(parser_data, options_parse_leaf, NULL, NULL);
		}
}
