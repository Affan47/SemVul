cr_parser_set_sac_handler (CRParser * a_this, CRDocHandler * a_handler)
{
        g_return_val_if_fail (a_this, CR_BAD_PARAM_ERROR);

        if (PRIVATE (a_this)->sac_handler) {
                cr_doc_handler_unref (PRIVATE (a_this)->sac_handler);
        }

        PRIVATE (a_this)->sac_handler = a_handler;
        cr_doc_handler_ref (a_handler);

        return CR_OK;
}
