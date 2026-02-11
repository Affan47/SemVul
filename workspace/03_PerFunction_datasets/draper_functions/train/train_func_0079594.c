math_buttons_set_subscript_cb (MathButtons* self, GtkButton* widget) {
	GtkToggleButton* button = NULL;
	GtkButton* _tmp0_ = NULL;
	GtkToggleButton* _tmp1_ = NULL;
	GtkToggleButton* _tmp2_ = NULL;
	gboolean _tmp3_ = FALSE;
	g_return_if_fail (self != NULL);
	g_return_if_fail (widget != NULL);
	_tmp0_ = widget;
	_tmp1_ = _g_object_ref0 (G_TYPE_CHECK_INSTANCE_TYPE (_tmp0_, GTK_TYPE_TOGGLE_BUTTON) ? ((GtkToggleButton*) _tmp0_) : NULL);
	button = _tmp1_;
	_tmp2_ = button;
	_tmp3_ = gtk_toggle_button_get_active (_tmp2_);
	if (_tmp3_) {
		MathEquation* _tmp4_ = NULL;
		MathEquation* _tmp5_ = NULL;
		gboolean _tmp6_ = FALSE;
		gboolean _tmp7_ = FALSE;
		_tmp4_ = self->priv->equation;
		math_equation_set_number_mode (_tmp4_, NUMBER_MODE_SUBSCRIPT);
		_tmp5_ = self->priv->equation;
		_tmp6_ = gtk_text_buffer_get_has_selection ((GtkTextBuffer*) _tmp5_);
		_tmp7_ = _tmp6_;
		if (!_tmp7_) {
			math_buttons_remove_trailing_spaces (self);
		}
	} else {
		MathEquation* _tmp8_ = NULL;
		NumberMode _tmp9_ = 0;
		NumberMode _tmp10_ = 0;
		_tmp8_ = self->priv->equation;
		_tmp9_ = math_equation_get_number_mode (_tmp8_);
		_tmp10_ = _tmp9_;
		if (_tmp10_ == NUMBER_MODE_SUBSCRIPT) {
			MathEquation* _tmp11_ = NULL;
			_tmp11_ = self->priv->equation;
			math_equation_set_number_mode (_tmp11_, NUMBER_MODE_NORMAL);
		}
	}
	_g_object_unref0 (button);
}
