math_equation_redo (MathEquation* self) {
	GList* _tmp0_ = NULL;
	GList* _tmp2_ = NULL;
	gconstpointer _tmp3_ = NULL;
	MathEquationState* _tmp4_ = NULL;
	MathEquationState* _tmp5_ = NULL;
	MathEquationState* _tmp6_ = NULL;
	MathEquationState* _tmp7_ = NULL;
	g_return_if_fail (self != NULL);
	_tmp0_ = self->priv->redo_stack;
	if (_tmp0_ == NULL) {
		const gchar* _tmp1_ = NULL;
		_tmp1_ = _ ("No redo history");
		math_equation_set_status (self, _tmp1_);
		return;
	}
	_tmp2_ = self->priv->redo_stack;
	_tmp3_ = g_list_nth_data (_tmp2_, (guint) 0);
	_tmp4_ = _math_equation_state_ref0 ((MathEquationState*) _tmp3_);
	_math_equation_state_unref0 (self->priv->state);
	self->priv->state = _tmp4_;
	_tmp5_ = self->priv->state;
	self->priv->redo_stack = g_list_remove (self->priv->redo_stack, _tmp5_);
	_tmp6_ = math_equation_get_current_state (self);
	self->priv->undo_stack = g_list_prepend (self->priv->undo_stack, _tmp6_);
	_tmp7_ = self->priv->state;
	math_equation_apply_state (self, _tmp7_);
}
