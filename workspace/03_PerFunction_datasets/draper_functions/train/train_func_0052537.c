cr_parser_parse_ident (CRParser * a_this, CRString ** a_str)
{
        enum CRStatus status = CR_OK;

        g_return_val_if_fail (a_this && PRIVATE (a_this)
                              && PRIVATE (a_this)->tknzr
                              && a_str, CR_BAD_PARAM_ERROR);

        status = cr_tknzr_parse_token (PRIVATE (a_this)->tknzr,
                                       IDENT_TK, NO_ET, a_str, NULL);
        return status;
}
