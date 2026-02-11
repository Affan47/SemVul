end_selector (CRDocHandler * a_this, CRSelector * a_selector_list)
{
        enum CRStatus status = CR_OK;
        ParsingContext *ctxt = NULL;
        ParsingContext **ctxtptr = NULL;

        g_return_if_fail (a_this);
	ctxtptr = &ctxt;
        status = cr_doc_handler_get_ctxt (a_this, (gpointer *) ctxtptr);
        g_return_if_fail (status == CR_OK && ctxt);
        g_return_if_fail (ctxt->cur_stmt && ctxt->stylesheet);

        if (ctxt->cur_stmt) {
                CRStatement *stmts = NULL;

                if (ctxt->cur_media_stmt) {
                        CRAtMediaRule *media_rule = NULL;

                        media_rule = ctxt->cur_media_stmt->kind.media_rule;

                        stmts = cr_statement_append
                                (media_rule->rulesets, ctxt->cur_stmt);

                        if (!stmts) {
                                cr_utils_trace_info
                                        ("Could not append a new statement");
                                cr_statement_destroy (media_rule->rulesets);
                                ctxt->cur_media_stmt->
                                        kind.media_rule->rulesets = NULL;
                                return;
                        }
                        media_rule->rulesets = stmts;
                        ctxt->cur_stmt = NULL;
                } else {
                        stmts = cr_statement_append
                                (ctxt->stylesheet->statements,
                                 ctxt->cur_stmt);
                        if (!stmts) {
                                cr_utils_trace_info
                                        ("Could not append a new statement");
                                cr_statement_destroy (ctxt->cur_stmt);
                                ctxt->cur_stmt = NULL;
                                return;
                        }
                        ctxt->stylesheet->statements = stmts;
                        ctxt->cur_stmt = NULL;
                }

        }
        a_selector_list = NULL;
}
