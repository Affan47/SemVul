end_selector (CRDocHandler * a_this,
              CRSelector *a_selector_list)
{
        struct SacContext *context = NULL;

        g_return_if_fail (a_this);

        cr_doc_handler_get_ctxt (a_this, (gpointer *) (gpointer) & context);
        if (context) {
                context->level--;
        }
        g_print (" }\n") ;
}
