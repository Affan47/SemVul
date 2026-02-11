parse_font_face_unrecoverable_error_cb (CRDocHandler * a_this)
{
        CRStatement *stmt = NULL;
	CRStatement **stmtptr = NULL;
        enum CRStatus status = CR_OK;

        g_return_if_fail (a_this);

	stmtptr = &stmt;
        status = cr_doc_handler_get_ctxt (a_this, (gpointer *) stmtptr);
        if (status != CR_OK) {
                cr_utils_trace_info ("Couldn't get parsing context. "
                                     "This may lead to some memory leaks.");
                return;
        }
        if (stmt) {
                cr_statement_destroy (stmt);
                cr_doc_handler_set_ctxt (a_this, NULL);
                return;
        }
}
