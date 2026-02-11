cr_term_parse_expression_from_buf (const guchar * a_buf,
                                   enum CREncoding a_encoding)
{
        CRTerm *result = NULL;
        enum CRStatus status = CR_OK;

        g_return_val_if_fail (a_buf, NULL);

        CRParser *parser = cr_parser_new_from_buf (
		                                 (guchar*)a_buf,
										  strlen ((char *)a_buf),
                                          a_encoding, FALSE);
        g_return_val_if_fail (parser, NULL);

        status = cr_parser_try_to_skip_spaces_and_comments (parser);
        if (status != CR_OK) {
                goto cleanup;
        }
        status = cr_parser_parse_expr (parser, &result);
        if (status != CR_OK) {
                if (result) {
                        cr_term_destroy (result);
                        result = NULL;
                }
        }

      cleanup:
        if (parser) {
                cr_parser_destroy (parser);
                parser = NULL;
        }

        return result;
}
