root_node_real_solve_r (RNode* base, Number* r) {
	RootNode * self;
	Number* result = NULL;
	Number* _tmp0_ = NULL;
	gint _tmp1_ = 0;
	Number* _tmp2_ = NULL;
	self = (RootNode*) base;
	g_return_val_if_fail (r != NULL, NULL);
	_tmp0_ = r;
	_tmp1_ = self->priv->n;
	_tmp2_ = number_root (_tmp0_, (gint64) _tmp1_);
	result = _tmp2_;
	return result;
}
