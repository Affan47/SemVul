gdm_settings_parse_schemas (const char  *file,
                            const char  *root,
                            GSList     **schemas)
{
        GMarkupParseContext *ctx;
        ParserInfo          *info;
        char                *contents;
        gsize                len;
        GError              *error;
        gboolean             res;

        g_return_val_if_fail (file != NULL, FALSE);
        g_return_val_if_fail (root != NULL, FALSE);

        g_assert (schemas != NULL);

        contents = NULL;
        error = NULL;
        res = g_file_get_contents (file, &contents, &len, &error);
        if (! res) {
                g_warning ("Unable to read schemas file: %s", error->message);
                g_error_free (error);
                return FALSE;
        }

        info = g_new0 (ParserInfo, 1);
        ctx = g_markup_parse_context_new (&parser, 0, info, NULL);
        g_markup_parse_context_parse (ctx, contents, len, NULL);

        *schemas = info->list;

        g_markup_parse_context_free (ctx);
        g_free (info);
        g_free (contents);

        return TRUE;
}
