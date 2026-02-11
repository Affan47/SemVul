_folks_individual_aggregator_connect_to_individual (FolksIndividualAggregator* self, FolksIndividual* individual) {
	FolksIndividual* _tmp0_ = NULL;
	GeeMap* _tmp1_ = NULL;
	FolksIndividual* _tmp2_ = NULL;
	const gchar* _tmp3_ = NULL;
	const gchar* _tmp4_ = NULL;
	FolksIndividual* _tmp5_ = NULL;
	g_return_if_fail (self != NULL);
	g_return_if_fail (individual != NULL);
	_tmp0_ = individual;
	g_signal_connect_object (_tmp0_, "removed", (GCallback) __folks_individual_aggregator_individual_removed_cb_folks_individual_removed, self, 0);
	_tmp1_ = self->priv->_individuals;
	_tmp2_ = individual;
	_tmp3_ = folks_individual_get_id (_tmp2_);
	_tmp4_ = _tmp3_;
	_tmp5_ = individual;
	gee_map_set (_tmp1_, _tmp4_, _tmp5_);
}
