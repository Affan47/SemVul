start_document (CRDocHandler * a_this)
{
        struct SacContext *context = NULL;

        g_return_if_fail (a_this);

        context = g_try_malloc (sizeof (struct SacContext));
        if (!context) {
                cr_utils_trace_info ("instanciation of sac context failed");
                return;
        }
        cr_doc_handler_set_ctxt (a_this, context);
}
