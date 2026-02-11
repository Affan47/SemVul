not_node_real_solve_r (RNode* base, Number* r) {
	NotNode * self;
	Number* result = NULL;
	Number* _tmp0_ = NULL;
	Parser* _tmp1_ = NULL;
	gint _tmp2_ = 0;
	gboolean _tmp3_ = FALSE;
	Number* _tmp6_ = NULL;
	Parser* _tmp7_ = NULL;
	gint _tmp8_ = 0;
	Number* _tmp9_ = NULL;
	self = (NotNode*) base;
	g_return_val_if_fail (r != NULL, NULL);
	_tmp0_ = r;
	_tmp1_ = ((ParseNode*) self)->parser;
	_tmp2_ = _tmp1_->wordlen;
	_tmp3_ = mp_is_overflow (_tmp0_, _tmp2_);
	if (!_tmp3_) {
		Parser* _tmp4_ = NULL;
		Number* _tmp5_ = NULL;
		_tmp4_ = ((ParseNode*) self)->parser;
		parser_set_error (_tmp4_, ERROR_CODE_OVERFLOW, NULL, (guint) 0, (guint) 0);
		_tmp5_ = number_new_integer ((gint64) 0);
		result = _tmp5_;
		return result;
	}
	_tmp6_ = r;
	_tmp7_ = ((ParseNode*) self)->parser;
	_tmp8_ = _tmp7_->wordlen;
	_tmp9_ = number_not (_tmp6_, _tmp8_);
	result = _tmp9_;
	return result;
}
