charset (CRDocHandler * a_this, CRString * a_charset,
         CRParsingLocation *a_location)
{
        enum CRStatus status = CR_OK;
        CRStatement *stmt = NULL,
                *stmt2 = NULL;
        CRString *charset = NULL;

        ParsingContext *ctxt = NULL;
        ParsingContext **ctxtptr = NULL;

        g_return_if_fail (a_this);
	ctxtptr = &ctxt;
        status = cr_doc_handler_get_ctxt (a_this, (gpointer *) ctxtptr);
        g_return_if_fail (status == CR_OK && ctxt);
        g_return_if_fail (ctxt->stylesheet);

        charset = cr_string_dup (a_charset) ;
        stmt = cr_statement_new_at_charset_rule (ctxt->stylesheet, charset);
        g_return_if_fail (stmt);
        stmt2 = cr_statement_append (ctxt->stylesheet->statements, stmt);
        if (!stmt2) {
                if (stmt) {
                        cr_statement_destroy (stmt);
                        stmt = NULL;
                }
                if (charset) {
                        cr_string_destroy (charset);
                }
                return;
        }
        ctxt->stylesheet->statements = stmt2;
        stmt2 = NULL;
}
