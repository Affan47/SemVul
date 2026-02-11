completion_provider_show_all_proposals (CompletionProvider* self, GtkSourceCompletionContext* context) {
	GtkSourceCompletionContext* _tmp0_ = NULL;
	GList* _tmp1_ = NULL;
	g_return_if_fail (self != NULL);
	g_return_if_fail (context != NULL);
	_tmp0_ = context;
	_tmp1_ = self->priv->_proposals;
	gtk_source_completion_context_add_proposals (_tmp0_, G_TYPE_CHECK_INSTANCE_CAST (self, gtk_source_completion_provider_get_type (), GtkSourceCompletionProvider), _tmp1_, TRUE);
}
