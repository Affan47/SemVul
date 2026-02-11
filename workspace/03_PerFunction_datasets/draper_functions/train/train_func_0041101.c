libisocodes_iso_codes_get_filepath (libisocodesISO_Codes* self) {
	gchar* result = NULL;
	const gchar* _tmp0_;
	gchar* _tmp1_;
	g_return_val_if_fail (self != NULL, NULL);
	_tmp0_ = self->priv->_filepath;
	_tmp1_ = g_strdup (_tmp0_);
	result = _tmp1_;
	return result;
}
