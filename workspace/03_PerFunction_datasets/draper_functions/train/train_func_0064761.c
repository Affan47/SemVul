cr_om_parser_parse_buf (CROMParser * a_this,
                        const guchar * a_buf,
                        gulong a_len,
                        enum CREncoding a_enc, CRStyleSheet ** a_result)
{

        enum CRStatus status = CR_OK;

        g_return_val_if_fail (a_this && a_result, CR_BAD_PARAM_ERROR);

        if (!PRIVATE (a_this)->parser) {
                PRIVATE (a_this)->parser = cr_parser_new (NULL);
        }

        status = cr_parser_parse_buf (PRIVATE (a_this)->parser,
                                      a_buf, a_len, a_enc);

        if (status == CR_OK) {
                CRStyleSheet *result = NULL;
                CRStyleSheet **resultptr = NULL;
                CRDocHandler *sac_handler = NULL;

                cr_parser_get_sac_handler (PRIVATE (a_this)->parser,
                                           &sac_handler);
                g_return_val_if_fail (sac_handler, CR_ERROR);
		resultptr = &result;
                status = cr_doc_handler_get_result (sac_handler,
                                                    (gpointer *) resultptr);
                g_return_val_if_fail (status == CR_OK, status);

                if (result)
                        *a_result = result;
        }

        return status;
}
