unity_internal_merge_strategy_merge_result (UnityInternalMergeStrategy* self, const gchar* source_scope_id, DeeModel* target, GVariant** row, int row_length1) {
	g_return_val_if_fail (self != NULL, NULL);
	return UNITY_INTERNAL_MERGE_STRATEGY_GET_INTERFACE (self)->merge_result (self, source_scope_id, target, row, row_length1);
}
