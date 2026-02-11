gtkaml_callable_get_parameters (GtkamlCallable* self) {
	ValaList* result = NULL;
	ValaSymbol* _tmp0_;
	ValaSymbol* _tmp3_;
	ValaList* _tmp4_ = NULL;
	g_return_val_if_fail (self != NULL, NULL);
	_tmp0_ = self->priv->_member;
	if (VALA_IS_METHOD (_tmp0_)) {
		ValaSymbol* _tmp1_;
		ValaList* _tmp2_ = NULL;
		_tmp1_ = self->priv->_member;
		_tmp2_ = vala_method_get_parameters (VALA_METHOD (_tmp1_));
		result = _tmp2_;
		return result;
	}
	_tmp3_ = self->priv->_member;
	_tmp4_ = vala_signal_get_parameters (VALA_SIGNAL (_tmp3_));
	result = _tmp4_;
	return result;
}
