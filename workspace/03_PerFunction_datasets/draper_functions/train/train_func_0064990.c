caribou_column_model_get_key (CaribouColumnModel* self, gint index) {
	CaribouKeyModel* result = NULL;
	GeeArrayList* _tmp0_ = NULL;
	gint _tmp1_ = 0;
	gpointer _tmp2_ = NULL;
	g_return_val_if_fail (self != NULL, NULL);
	_tmp0_ = self->priv->keys;
	_tmp1_ = index;
	_tmp2_ = gee_abstract_list_get ((GeeAbstractList*) _tmp0_, _tmp1_);
	result = (CaribouKeyModel*) _tmp2_;
	return result;
}
