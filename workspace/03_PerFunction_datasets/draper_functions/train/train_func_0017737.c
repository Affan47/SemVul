create_preset_from_xml_file(gchar *filename, GError **error)
{
    GError *err = NULL;
    gchar *contents;

    if (g_file_get_contents(filename, &contents, NULL, &err) == FALSE) {
        g_warning("Failed to get %s contents: %s", filename, err->message);
        *error = g_error_copy(err);
        g_error_free(err);
        return NULL;
    }

    AppData *ad = g_slice_new(AppData);
    ad->depth = 0;
    ad->preset = g_slice_new(Preset);
    ad->preset->name = NULL;
    ad->preset->params = NULL;
    ad->preset->genetxs = NULL;
    ad->id = PARSER_TYPE_NOT_SET;

    XML_Parser p;
    p = XML_ParserCreate(NULL);
    XML_SetUserData(p, (void *) ad);
    XML_SetElementHandler(p, start, end);
    XML_SetCharacterDataHandler(p, text_cb);

    if (XML_Parse(p, contents, strlen(contents), XML_TRUE) != XML_STATUS_OK) {
        g_set_error(error, 0, 0, "Parse error at line %d:\n%s",
                    (int)XML_GetCurrentLineNumber(p),
                    XML_ErrorString(XML_GetErrorCode(p)));
        preset_free(ad->preset);
        g_slice_free(AppData, ad);
        g_free(contents);
        return NULL;
    }

    Preset *preset = ad->preset;
    preset->params = g_list_reverse(preset->params);
    preset->genetxs = g_list_reverse(preset->genetxs);

    XML_ParserFree(p);
    g_slice_free(AppData, ad);

    g_free(contents);
    return preset;
}
