math_equation_delete_next (MathEquation* self) {
	gint cursor = 0;
	gint _tmp0_ = 0;
	gint _tmp1_ = 0;
	GtkTextIter start = {0};
	GtkTextIter end = {0};
	gint _tmp2_ = 0;
	GtkTextIter _tmp3_ = {0};
	gint _tmp4_ = 0;
	GtkTextIter _tmp5_ = {0};
	g_return_if_fail (self != NULL);
	g_object_get ((GObject*) self, "cursor-position", &cursor, NULL, NULL);
	_tmp0_ = cursor;
	_tmp1_ = gtk_text_buffer_get_char_count ((GtkTextBuffer*) self);
	if (_tmp0_ >= _tmp1_) {
		return;
	}
	_tmp2_ = cursor;
	gtk_text_buffer_get_iter_at_offset ((GtkTextBuffer*) self, &_tmp3_, _tmp2_);
	start = _tmp3_;
	_tmp4_ = cursor;
	gtk_text_buffer_get_iter_at_offset ((GtkTextBuffer*) self, &_tmp5_, _tmp4_ + 1);
	end = _tmp5_;
	gtk_text_buffer_delete ((GtkTextBuffer*) self, &start, &end);
}
