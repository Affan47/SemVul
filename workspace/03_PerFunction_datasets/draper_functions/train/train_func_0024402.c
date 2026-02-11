test_equation_real_variable_is_defined (Equation* base, const gchar* name) {
	TestEquation * self;
	gboolean result = FALSE;
	gboolean _tmp0_;
	gboolean _tmp1_ = FALSE;
	const gchar* _tmp2_;
	gboolean _tmp4_;
	self = (TestEquation*) base;
	g_return_val_if_fail (name != NULL, FALSE);
	_tmp0_ = self->priv->enable_variables;
	if (!_tmp0_) {
		result = FALSE;
		return result;
	}
	_tmp2_ = name;
	if (g_strcmp0 (_tmp2_, "x") == 0) {
		_tmp1_ = TRUE;
	} else {
		const gchar* _tmp3_;
		_tmp3_ = name;
		_tmp1_ = g_strcmp0 (_tmp3_, "y") == 0;
	}
	_tmp4_ = _tmp1_;
	result = _tmp4_;
	return result;
}
