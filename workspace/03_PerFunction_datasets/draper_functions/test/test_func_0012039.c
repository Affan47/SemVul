parser_start_cb (GMarkupParseContext  *context,
                 const gchar          *node_name,
                 const gchar         **attribute_names,
                 const gchar         **attribute_values,
                 gpointer              user_data,
                 GError              **error)
{
	DefaultData *data = user_data;

        if (g_ascii_strcasecmp (node_name, "applyto") == 0) {
                data->text = g_string_new (NULL);
        }
        else if (g_ascii_strcasecmp (node_name, "type") == 0) {
                data->text = g_string_new (NULL);
        }
        else if (g_ascii_strcasecmp (node_name, "default") == 0) {
                data->text = g_string_new (NULL);
        }
}
