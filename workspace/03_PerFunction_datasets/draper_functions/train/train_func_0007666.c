function_node_real_solve_r (RNode* base, Number* r) {
	FunctionNode * self;
	Number* result = NULL;
	Number* ans = NULL;
	Parser* _tmp0_ = NULL;
	LexerToken* _tmp1_ = NULL;
	const gchar* _tmp2_ = NULL;
	Number* _tmp3_ = NULL;
	Number* _tmp4_ = NULL;
	Number* _tmp5_ = NULL;
	self = (FunctionNode*) base;
	g_return_val_if_fail (r != NULL, NULL);
	_tmp0_ = ((ParseNode*) self)->parser;
	_tmp1_ = ((ParseNode*) self)->token;
	_tmp2_ = _tmp1_->text;
	_tmp3_ = r;
	_tmp4_ = parser_get_function (_tmp0_, _tmp2_, _tmp3_);
	ans = _tmp4_;
	_tmp5_ = ans;
	if (_tmp5_ == NULL) {
		Parser* _tmp6_ = NULL;
		LexerToken* _tmp7_ = NULL;
		const gchar* _tmp8_ = NULL;
		LexerToken* _tmp9_ = NULL;
		guint _tmp10_ = 0U;
		LexerToken* _tmp11_ = NULL;
		guint _tmp12_ = 0U;
		_tmp6_ = ((ParseNode*) self)->parser;
		_tmp7_ = ((ParseNode*) self)->token;
		_tmp8_ = _tmp7_->text;
		_tmp9_ = ((ParseNode*) self)->token;
		_tmp10_ = _tmp9_->start_index;
		_tmp11_ = ((ParseNode*) self)->token;
		_tmp12_ = _tmp11_->end_index;
		parser_set_error (_tmp6_, ERROR_CODE_UNKNOWN_FUNCTION, _tmp8_, _tmp10_, _tmp12_);
	}
	result = ans;
	return result;
}
