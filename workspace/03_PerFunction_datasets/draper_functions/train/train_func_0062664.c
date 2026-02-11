cr_parser_parse_uri (CRParser * a_this, CRString ** a_str)
{

        enum CRStatus status = CR_PARSING_ERROR;

        g_return_val_if_fail (a_this && PRIVATE (a_this)
                              && PRIVATE (a_this)->tknzr, CR_BAD_PARAM_ERROR);

        status = cr_tknzr_parse_token (PRIVATE (a_this)->tknzr,
                                       URI_TK, NO_ET, a_str, NULL);
        return status;
}
