serializer_from_string (Serializer* self, const gchar* str) {
	Number* result = NULL;
	const gchar* _tmp0_ = NULL;
	gint _tmp1_ = 0;
	Number* _tmp2_ = NULL;
	g_return_val_if_fail (self != NULL, NULL);
	g_return_val_if_fail (str != NULL, NULL);
	_tmp0_ = str;
	_tmp1_ = self->priv->number_base;
	_tmp2_ = mp_set_from_string (_tmp0_, _tmp1_);
	result = _tmp2_;
	return result;
}
