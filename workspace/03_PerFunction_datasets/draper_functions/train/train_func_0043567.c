unity_internal_results_synchronizer_real_merge_result (UnityInternalMergeStrategy* base, const gchar* source_scope_id, DeeModel* target, GVariant** row, int row_length1) {
	UnityInternalResultsSynchronizer * self;
	DeeModelIter* result = NULL;
	DeeModel* _tmp0_ = NULL;
	GVariant** _tmp1_ = NULL;
	gint _tmp1__length1 = 0;
	DeeModelIter* _tmp2_ = NULL;
	self = (UnityInternalResultsSynchronizer*) base;
	g_return_val_if_fail (source_scope_id != NULL, NULL);
	g_return_val_if_fail (target != NULL, NULL);
	_tmp0_ = target;
	_tmp1_ = row;
	_tmp1__length1 = row_length1;
	_tmp2_ = dee_model_append_row (_tmp0_, _tmp1_);
	result = _tmp2_;
	return result;
}
