options_parse_bar(GQParserData *parser_data, GMarkupParseContext *context, const gchar *element_name, const gchar **attribute_names, const gchar **attribute_values, gpointer data, GError **error)
{
	GtkWidget *bar = data;
	if (g_ascii_strcasecmp(element_name, "pane_comment") == 0)
		{
		GtkWidget *pane = bar_find_pane_by_id(bar, PANE_COMMENT, options_get_id(attribute_names, attribute_values));
		if (pane)
			{
			bar_pane_comment_update_from_config(pane, attribute_names, attribute_values);
			}
		else
			{
			pane = bar_pane_comment_new_from_config(attribute_names, attribute_values);
			bar_add(bar, pane);
			}
		options_parse_func_push(parser_data, options_parse_leaf, NULL, NULL);
		}
#ifdef HAVE_LIBCHAMPLAIN
#ifdef HAVE_LIBCHAMPLAIN_GTK
	else if (g_ascii_strcasecmp(element_name, "pane_gps") == 0)
		{
		GtkWidget *pane = bar_find_pane_by_id(bar, PANE_GPS, options_get_id(attribute_names, attribute_values));
		if (pane)
			{
			bar_pane_gps_update_from_config(pane, attribute_names, attribute_values);
			}
		else
			{
			pane = bar_pane_gps_new_from_config(attribute_names, attribute_values);
			bar_add(bar, pane);
			}
		options_parse_func_push(parser_data, options_parse_leaf, NULL, NULL);
		}
#endif
#endif
	else if (g_ascii_strcasecmp(element_name, "pane_exif") == 0)
		{
		GtkWidget *pane = bar_find_pane_by_id(bar, PANE_EXIF, options_get_id(attribute_names, attribute_values));
		if (pane)
			{
			bar_pane_exif_update_from_config(pane, attribute_names, attribute_values);
			}
		else
			{
			pane = bar_pane_exif_new_from_config(attribute_names, attribute_values);
			bar_add(bar, pane);
			}
		options_parse_func_push(parser_data, options_parse_pane_exif, NULL, pane);
		}
	else if (g_ascii_strcasecmp(element_name, "pane_histogram") == 0)
		{
		GtkWidget *pane = bar_find_pane_by_id(bar, PANE_HISTOGRAM, options_get_id(attribute_names, attribute_values));
		if (pane)
			{
			bar_pane_histogram_update_from_config(pane, attribute_names, attribute_values);
			}
		else
			{
			pane = bar_pane_histogram_new_from_config(attribute_names, attribute_values);
			bar_add(bar, pane);
			}
		options_parse_func_push(parser_data, options_parse_leaf, NULL, NULL);
		}
	else if (g_ascii_strcasecmp(element_name, "pane_keywords") == 0)
		{
		GtkWidget *pane = bar_find_pane_by_id(bar, PANE_KEYWORDS, options_get_id(attribute_names, attribute_values));
		if (pane)
			{
			bar_pane_keywords_update_from_config(pane, attribute_names, attribute_values);
			}
		else
			{
			pane = bar_pane_keywords_new_from_config(attribute_names, attribute_values);
			bar_add(bar, pane);
			}
		options_parse_func_push(parser_data, options_parse_leaf, NULL, NULL);
		}
	else if (g_ascii_strcasecmp(element_name, "clear") == 0)
		{
		bar_clear(bar);
		options_parse_func_push(parser_data, options_parse_leaf, NULL, NULL);
		}
	else
		{
		log_printf("unexpected in <bar>: <%s>\n", element_name);
		options_parse_func_push(parser_data, options_parse_leaf, NULL, NULL);
		}
}
