math_equation_get_error_token_start (MathEquation* self) {
	guint result;
	gint ans_start = 0;
	gint ans_end = 0;
	gint _tmp0_ = 0;
	gint _tmp1_ = 0;
	gboolean _tmp2_ = FALSE;
	gint _tmp3_ = 0;
	gboolean _tmp7_ = FALSE;
	MathEquationState* _tmp12_ = NULL;
	guint _tmp13_ = 0U;
	g_return_val_if_fail (self != NULL, 0U);
	math_equation_get_ans_offsets (self, &_tmp0_, &_tmp1_);
	ans_start = _tmp0_;
	ans_end = _tmp1_;
	_tmp3_ = ans_start;
	if (_tmp3_ != (-1)) {
		gint _tmp4_ = 0;
		MathEquationState* _tmp5_ = NULL;
		guint _tmp6_ = 0U;
		_tmp4_ = ans_start;
		_tmp5_ = self->priv->state;
		_tmp6_ = _tmp5_->error_token_start;
		_tmp2_ = ((guint) _tmp4_) < _tmp6_;
	} else {
		_tmp2_ = FALSE;
	}
	_tmp7_ = _tmp2_;
	if (_tmp7_) {
		MathEquationState* _tmp8_ = NULL;
		guint _tmp9_ = 0U;
		gint _tmp10_ = 0;
		gint _tmp11_ = 0;
		_tmp8_ = self->priv->state;
		_tmp9_ = _tmp8_->error_token_start;
		_tmp10_ = ans_end;
		_tmp11_ = ans_start;
		result = ((_tmp9_ + _tmp10_) - _tmp11_) - 3;
		return result;
	}
	_tmp12_ = self->priv->state;
	_tmp13_ = _tmp12_->error_token_start;
	result = _tmp13_;
	return result;
}
