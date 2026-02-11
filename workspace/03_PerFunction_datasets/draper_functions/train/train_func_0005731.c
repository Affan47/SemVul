string_index_of_nth_char (const gchar* self, glong c) {
	gint result = 0;
	glong _tmp0_ = 0L;
	gchar* _tmp1_ = NULL;
	g_return_val_if_fail (self != NULL, 0);
	_tmp0_ = c;
	_tmp1_ = g_utf8_offset_to_pointer (self, _tmp0_);
	result = (gint) (_tmp1_ - ((gchar*) self));
	return result;
}
