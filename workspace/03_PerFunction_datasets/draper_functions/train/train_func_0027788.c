cr_statement_at_import_rule_parse_from_buf (const guchar * a_buf,
                                            enum CREncoding a_encoding)
{
        enum CRStatus status = CR_OK;
        CRParser *parser = NULL;
        CRStatement *result = NULL;
        GList *media_list = NULL;
        CRString *import_string = NULL;
        CRParsingLocation location = {0,0,0} ;

        parser = cr_parser_new_from_buf ((guchar*)a_buf,
		                                 strlen ((char *)a_buf),
                                         a_encoding, FALSE);
        if (!parser) {
                cr_utils_trace_info ("Instanciation of parser failed.");
                goto cleanup;
        }

        status = cr_parser_try_to_skip_spaces_and_comments (parser);
        if (status != CR_OK)
                goto cleanup;

        status = cr_parser_parse_import (parser,
                                         &media_list,
                                         &import_string,
                                         &location);
        if (status != CR_OK || !import_string)
                goto cleanup;

        result = cr_statement_new_at_import_rule (NULL, import_string,
                                                  media_list, NULL);
        if (result) {
                cr_parsing_location_copy (&result->location,
                                          &location) ;
                import_string = NULL;
                media_list = NULL;
        }

 cleanup:
        if (parser) {
                cr_parser_destroy (parser);
                parser = NULL;
        }
        if (media_list) {
                GList *cur = NULL;

                for (cur = media_list; media_list;
                     media_list = g_list_next (media_list)) {
                        if (media_list->data) {
                                cr_string_destroy ((CRString*)media_list->data);
                                media_list->data = NULL;
                        }
                }
                g_list_free (media_list);
                media_list = NULL;
        }
        if (import_string) {
                cr_string_destroy (import_string);
                import_string = NULL;
        }

        return result;
}
