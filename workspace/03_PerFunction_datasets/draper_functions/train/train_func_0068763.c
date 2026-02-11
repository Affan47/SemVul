document_structure_add_item_data (DocumentStructure* self, StructData* data) {
	GtkTreeIter* result = NULL;
	StructData _tmp0_ = {0};
	const gchar* _tmp1_ = NULL;
	StructureModel* _tmp3_ = NULL;
	StructData _tmp4_ = {0};
	GtkTreeIter* _tmp5_ = NULL;
	g_return_val_if_fail (self != NULL, NULL);
	g_return_val_if_fail (data != NULL, NULL);
	_tmp0_ = *data;
	_tmp1_ = _tmp0_.text;
	if (_tmp1_ == NULL) {
		gchar* _tmp2_ = NULL;
		_tmp2_ = g_strdup ("");
		_g_free0 ((*data).text);
		(*data).text = _tmp2_;
	}
	_tmp3_ = self->priv->_model;
	_tmp4_ = *data;
	_tmp5_ = structure_model_add_item_at_end (_tmp3_, &_tmp4_);
	result = _tmp5_;
	return result;
}
