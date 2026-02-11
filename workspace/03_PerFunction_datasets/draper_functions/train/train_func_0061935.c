parse_at_media_unrecoverable_error_cb (CRDocHandler * a_this)
{
        enum CRStatus status = CR_OK;
        CRStatement *stmt = NULL;
        CRStatement **stmtptr = NULL;

        g_return_if_fail (a_this);

	stmtptr = &stmt;
        status = cr_doc_handler_get_result (a_this, (gpointer *) stmtptr);
        if (status != CR_OK) {
                cr_utils_trace_info ("Couldn't get parsing context. "
                                     "This may lead to some memory leaks.");
                return;
        }
        if (stmt) {
                cr_statement_destroy (stmt);
                stmt = NULL;
                cr_doc_handler_set_ctxt (a_this, NULL);
                cr_doc_handler_set_result (a_this, NULL);
        }
}
