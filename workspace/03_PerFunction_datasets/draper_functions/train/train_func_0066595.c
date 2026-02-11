number_is_negative (Number* self) {
	gboolean result = FALSE;
	gint _tmp0_ = 0;
	g_return_val_if_fail (self != NULL, FALSE);
	_tmp0_ = self->re_sign;
	result = _tmp0_ < 0;
	return result;
}
