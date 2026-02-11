parse_at_media_start_selector_cb (CRDocHandler * a_this,
                                  CRSelector * a_sellist)
{
        enum CRStatus status = CR_OK;
        CRStatement *at_media = NULL;
        CRStatement **at_media_ptr = NULL;
	CRStatement *ruleset = NULL;

        g_return_if_fail (a_this && a_this->priv && a_sellist);

	at_media_ptr = &at_media;
        status = cr_doc_handler_get_ctxt (a_this, (gpointer *) at_media_ptr);
        g_return_if_fail (status == CR_OK && at_media);
        g_return_if_fail (at_media->type == AT_MEDIA_RULE_STMT);
        ruleset = cr_statement_new_ruleset (NULL, a_sellist, NULL, at_media);
        g_return_if_fail (ruleset);
        status = cr_doc_handler_set_ctxt (a_this, ruleset);
        g_return_if_fail (status == CR_OK);
}
