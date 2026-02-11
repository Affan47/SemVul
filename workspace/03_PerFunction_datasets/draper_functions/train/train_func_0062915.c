readMET(metdata * met, const char *filename)
{
    GMarkupParseContext *context;
    gchar *contents;
    MatchEquityParser *parser;
    gsize size;
    GError *error = NULL;

    initMD(met);
    met->mi.szFileName = g_strdup(filename);


    parser = g_new0(MatchEquityParser, 1);
    parser->filename = g_strdup(filename);
    parser->data = met;
    parser->state = STATE_NONE;
    parser->i = 0;
    parser->j = 0;

    if (!(context = g_markup_parse_context_new(&markup_parser, 0, parser, met_parser_destroy))) {
        g_warning("Can't create XML parser\n");
        g_free(parser);
        return -1;
    }


    if (!g_file_get_contents(filename, &contents, &size, &error)) {
        g_warning("Error reading XML file: %s\n", error->message);
        goto err;
    }


    if (!g_markup_parse_context_parse(context, contents, size, &error)) {
        g_warning("Error parsing XML file: %s\n", error->message);
        goto err;
    }

  err:
    g_markup_parse_context_free(context);
    g_free(contents);

    if (error) {
        g_error_free(error);
        return -1;
    } else {
        return 0;
    }
}
