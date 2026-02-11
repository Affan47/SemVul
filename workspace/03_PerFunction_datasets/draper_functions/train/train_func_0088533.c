map_get_height (Map* self) {
	guint result;
	gint h = 0;
	GList* _tmp0_ = NULL;
	gint _tmp7_ = 0;
	g_return_val_if_fail (self != NULL, 0U);
	h = 0;
	_tmp0_ = self->slots;
	{
		GList* slot_collection = NULL;
		GList* slot_it = NULL;
		slot_collection = _tmp0_;
		for (slot_it = slot_collection; slot_it != NULL; slot_it = slot_it->next) {
			Slot* _tmp1_ = NULL;
			Slot* slot = NULL;
			_tmp1_ = _slot_ref0 ((Slot*) slot_it->data);
			slot = _tmp1_;
			{
				Slot* _tmp2_ = NULL;
				gint _tmp3_ = 0;
				gint _tmp4_ = 0;
				_tmp2_ = slot;
				_tmp3_ = _tmp2_->y;
				_tmp4_ = h;
				if (_tmp3_ > _tmp4_) {
					Slot* _tmp5_ = NULL;
					gint _tmp6_ = 0;
					_tmp5_ = slot;
					_tmp6_ = _tmp5_->y;
					h = _tmp6_;
				}
				_slot_unref0 (slot);
			}
		}
	}
	_tmp7_ = h;
	result = (guint) (_tmp7_ + 2);
	return result;
}
