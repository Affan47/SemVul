cr_statement_at_page_rule_parse_from_buf (const guchar * a_buf,
                                          enum CREncoding a_encoding)
{
        enum CRStatus status = CR_OK;
        CRDocHandler *sac_handler = NULL;
        CRStatement *result = NULL;
        CRStatement **resultptr = NULL;

        g_return_val_if_fail (a_buf, NULL);

        CRParser *parser = cr_parser_new_from_buf ((guchar*)a_buf,
		                                 strlen ((char *)a_buf),
                                         a_encoding, FALSE);
        if (!parser) {
                cr_utils_trace_info ("Instanciation of the parser failed.");
                goto cleanup;
        }

        sac_handler = cr_doc_handler_new ();
        if (!sac_handler) {
                cr_utils_trace_info
                        ("Instanciation of the sac handler failed.");
                goto cleanup;
        }

        sac_handler->start_page = parse_page_start_page_cb;
        sac_handler->property = parse_page_property_cb;
        sac_handler->end_page = parse_page_end_page_cb;
        sac_handler->unrecoverable_error = parse_page_unrecoverable_error_cb;

        status = cr_parser_set_sac_handler (parser, sac_handler);
        if (status != CR_OK)
                goto cleanup;


        cr_parser_try_to_skip_spaces_and_comments (parser);
        if (status != CR_OK)
                goto cleanup;
        status = cr_parser_parse_page (parser);
        if (status != CR_OK)
                goto cleanup;

	resultptr = &result;
        status = cr_doc_handler_get_result (sac_handler,
                                            (gpointer *) resultptr);

      cleanup:

        if (parser) {
                cr_parser_destroy (parser);
                parser = NULL;
                sac_handler = NULL ;
        }
        if (sac_handler) {
                cr_doc_handler_unref (sac_handler);
                sac_handler = NULL;
        }
        return result;
}
