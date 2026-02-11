parser_cxx_assist_populate_real (ParserCxxAssist* assist, gboolean finished)
{
	g_assert (assist->priv->pre_word != NULL);
	GList* proposals = anjuta_completion_complete (assist->priv->completion_cache,
	                                               assist->priv->pre_word,
	                                               -1);
	anjuta_language_provider_proposals (assist->priv->lang_prov,
	                                    IANJUTA_PROVIDER(assist), proposals,
	                                    assist->priv->pre_word, finished);
	g_list_free (proposals);
}
