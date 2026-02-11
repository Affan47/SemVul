structure_model_iter_is_valid (StructureModel* self, GtkTreeIter* iter) {
	gboolean result = FALSE;
	GtkTreeIter _tmp0_ = {0};
	gint _tmp1_ = 0;
	gint _tmp2_ = 0;
	GtkTreeIter _tmp3_ = {0};
	void* _tmp4_ = NULL;
	GNode* node = NULL;
	GtkTreeIter _tmp5_ = {0};
	GNode* _tmp6_ = NULL;
	GNode* _tmp7_ = NULL;
	gconstpointer _tmp8_ = NULL;
	StructData data = {0};
	GNode* _tmp9_ = NULL;
	gconstpointer _tmp10_ = NULL;
	StructData _tmp11_ = {0};
	StructData _tmp12_ = {0};
	const gchar* _tmp13_ = NULL;
	g_return_val_if_fail (self != NULL, FALSE);
	g_return_val_if_fail (iter != NULL, FALSE);
	_tmp0_ = *iter;
	_tmp1_ = _tmp0_.stamp;
	_tmp2_ = self->priv->_stamp;
	if (_tmp1_ != _tmp2_) {
		result = FALSE;
		return result;
	}
	_tmp3_ = *iter;
	_tmp4_ = _tmp3_.user_data;
	if (_tmp4_ == NULL) {
		result = FALSE;
		return result;
	}
	_tmp5_ = *iter;
	_tmp6_ = structure_model_get_node_from_iter (self, &_tmp5_);
	node = _tmp6_;
	_tmp7_ = node;
	_tmp8_ = _tmp7_->data;
	if (((StructData*) _tmp8_) == NULL) {
		result = FALSE;
		return result;
	}
	_tmp9_ = node;
	_tmp10_ = _tmp9_->data;
	struct_data_copy ((StructData*) _tmp10_, &_tmp11_);
	data = _tmp11_;
	_tmp12_ = data;
	_tmp13_ = _tmp12_.text;
	if (_tmp13_ == NULL) {
		result = FALSE;
		struct_data_destroy (&data);
		return result;
	}
	result = TRUE;
	struct_data_destroy (&data);
	return result;
}
