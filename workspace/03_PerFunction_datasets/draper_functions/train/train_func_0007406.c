handle_start_element (GMarkupParseContext *context,
		      const gchar         *name,
		      const gchar        **attr_names,
		      const gchar        **attr_values,
		      gpointer             user_data,
		      GError             **err)
{
    Parser *parser = user_data;

    if (strcmp (name, "output") == 0)
    {
	int i;
	g_assert (parser->output == NULL);

	parser->output = g_new0 (GnomeOutputInfo, 1);
	parser->output->rotation = 0;

	for (i = 0; attr_names[i] != NULL; ++i)
	{
	    if (strcmp (attr_names[i], "name") == 0)
	    {
		parser->output->name = g_strdup (attr_values[i]);
		break;
	    }
	}

	if (!parser->output->name)
	{


	    g_warning ("Malformed monitor configuration file");

	    parser->output->name = g_strdup ("default");
	}
	parser->output->connected = FALSE;
	parser->output->on = FALSE;
	parser->output->primary = FALSE;
    }
    else if (strcmp (name, "configuration") == 0)
    {
	g_assert (parser->configuration == NULL);

	parser->configuration = g_new0 (GnomeRRConfig, 1);
	parser->configuration->clone = FALSE;
	parser->configuration->outputs = NULL;
    }
    else if (strcmp (name, "monitors") == 0)
    {
	int i;

	for (i = 0; attr_names[i] != NULL; i++)
	{
	    if (strcmp (attr_names[i], "version") == 0)
	    {
		parser->config_file_version = parse_int (attr_values[i]);
		break;
	    }
	}
    }

    g_queue_push_tail (parser->stack, g_strdup (name));
}
