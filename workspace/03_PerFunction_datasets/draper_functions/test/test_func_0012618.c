math_equation_get_is_empty (MathEquation* self) {
	gboolean result;
	gint _tmp0_ = 0;
	g_return_val_if_fail (self != NULL, FALSE);
	_tmp0_ = gtk_text_buffer_get_char_count ((GtkTextBuffer*) self);
	result = _tmp0_ == 0;
	return result;
}
