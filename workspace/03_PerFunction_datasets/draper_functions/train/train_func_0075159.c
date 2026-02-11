parser_get_associativity_p (Parser* self, Precedence type) {
	Associativity result = 0;
	gboolean _tmp0_ = FALSE;
	gboolean _tmp1_ = FALSE;
	gboolean _tmp2_ = FALSE;
	gboolean _tmp3_ = FALSE;
	Precedence _tmp4_ = 0;
	gboolean _tmp6_ = FALSE;
	gboolean _tmp8_ = FALSE;
	gboolean _tmp10_ = FALSE;
	gboolean _tmp12_ = FALSE;
	Precedence _tmp13_ = 0;
	g_return_val_if_fail (self != NULL, 0);
	_tmp4_ = type;
	if (_tmp4_ == PRECEDENCE_BOOLEAN) {
		_tmp3_ = TRUE;
	} else {
		Precedence _tmp5_ = 0;
		_tmp5_ = type;
		_tmp3_ = _tmp5_ == PRECEDENCE_DIVIDE;
	}
	_tmp6_ = _tmp3_;
	if (_tmp6_) {
		_tmp2_ = TRUE;
	} else {
		Precedence _tmp7_ = 0;
		_tmp7_ = type;
		_tmp2_ = _tmp7_ == PRECEDENCE_MOD;
	}
	_tmp8_ = _tmp2_;
	if (_tmp8_) {
		_tmp1_ = TRUE;
	} else {
		Precedence _tmp9_ = 0;
		_tmp9_ = type;
		_tmp1_ = _tmp9_ == PRECEDENCE_MULTIPLY;
	}
	_tmp10_ = _tmp1_;
	if (_tmp10_) {
		_tmp0_ = TRUE;
	} else {
		Precedence _tmp11_ = 0;
		_tmp11_ = type;
		_tmp0_ = _tmp11_ == PRECEDENCE_ADD_SUBTRACT;
	}
	_tmp12_ = _tmp0_;
	if (_tmp12_) {
		result = ASSOCIATIVITY_LEFT;
		return result;
	}
	_tmp13_ = type;
	if (_tmp13_ == PRECEDENCE_POWER) {
		result = ASSOCIATIVITY_RIGHT;
		return result;
	}
	result = ASSOCIATIVITY_LEFT;
	return result;
}
