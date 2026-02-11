cr_parser_destroy (CRParser * a_this)
{
        g_return_if_fail (a_this && PRIVATE (a_this));

        if (PRIVATE (a_this)->tknzr) {
                if (cr_tknzr_unref (PRIVATE (a_this)->tknzr) == TRUE)
                        PRIVATE (a_this)->tknzr = NULL;
        }

        if (PRIVATE (a_this)->sac_handler) {
                cr_doc_handler_unref (PRIVATE (a_this)->sac_handler);
                PRIVATE (a_this)->sac_handler = NULL;
        }

        if (PRIVATE (a_this)->err_stack) {
                cr_parser_clear_errors (a_this);
                PRIVATE (a_this)->err_stack = NULL;
        }

        if (PRIVATE (a_this)) {
                g_free (PRIVATE (a_this));
                PRIVATE (a_this) = NULL;
        }

        if (a_this) {
                g_free (a_this);
                a_this = NULL;
        }
}
