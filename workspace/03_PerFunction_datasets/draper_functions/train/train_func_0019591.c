canvas_start_choice (Canvas* self, gchar ch) {
	GList* _tmp0_ = NULL;
	gboolean _tmp1_;
	GList* boxes;
	gchar* _tmp2_ = NULL;
	gchar* str;
	g_return_if_fail (self != NULL);
	_tmp1_ = g_ascii_isdigit (ch);
	if (_tmp1_) {
		_tmp0_ = self->priv->digit_boxes;
	} else {
		_tmp0_ = self->priv->mult_boxes;
	}
	boxes = _tmp0_;
	_tmp2_ = g_strdup_printf ("%c", (gint) ch);
	str = _tmp2_;
	{
		GList* b_collection;
		GList* b_it;
		b_collection = boxes;
		for (b_it = b_collection; b_it != NULL; b_it = b_it->next) {
			CharBox* _tmp3_;
			CharBox* b;
			_tmp3_ = _g_object_ref0 ((CharBox*) b_it->data);
			b = _tmp3_;
			{
				const gchar* _tmp4_ = NULL;
				_tmp4_ = char_box_get_letter (b);
				if (g_strcmp0 (str, _tmp4_) == 0) {
					gboolean _tmp5_;
					_tmp5_ = g_ascii_isdigit (ch);
					if (_tmp5_) {
						canvas_start_digit_choice (self, b);
					} else {
						canvas_start_char_choice (self, b);
					}
					_g_object_unref0 (b);
					break;
				}
				_g_object_unref0 (b);
			}
		}
	}
	_g_free0 (str);
}
