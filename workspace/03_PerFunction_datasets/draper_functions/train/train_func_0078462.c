caribou_keyboard_model_on_key_released (CaribouKeyboardModel* self, CaribouKeyModel* key) {
	CaribouKeyModel* _tmp0_ = NULL;
	gboolean _tmp1_ = FALSE;
	gboolean _tmp2_ = FALSE;
	g_return_if_fail (self != NULL);
	g_return_if_fail (key != NULL);
	_tmp0_ = key;
	_tmp1_ = caribou_key_model_get_is_modifier (_tmp0_);
	_tmp2_ = _tmp1_;
	if (!_tmp2_) {
		CaribouKeyModel** modifiers = NULL;
		GeeHashSet* _tmp3_ = NULL;
		gint _tmp4_ = 0;
		gpointer* _tmp5_ = NULL;
		gint modifiers_length1 = 0;
		gint _modifiers_size_ = 0;
		CaribouKeyModel** _tmp6_ = NULL;
		gint _tmp6__length1 = 0;
		_tmp3_ = self->priv->active_mod_keys;
		_tmp5_ = gee_collection_to_array ((GeeCollection*) _tmp3_, &_tmp4_);
		modifiers = (CaribouKeyModel**) _tmp5_;
		modifiers_length1 = (_tmp4_ * sizeof (CaribouKeyModel*)) / sizeof (CaribouKeyModel*);
		_modifiers_size_ = modifiers_length1;
		_tmp6_ = modifiers;
		_tmp6__length1 = modifiers_length1;
		{
			CaribouKeyModel** modifier_collection = NULL;
			gint modifier_collection_length1 = 0;
			gint _modifier_collection_size_ = 0;
			gint modifier_it = 0;
			modifier_collection = _tmp6_;
			modifier_collection_length1 = _tmp6__length1;
			for (modifier_it = 0; modifier_it < _tmp6__length1; modifier_it = modifier_it + 1) {
				CaribouKeyModel* _tmp7_ = NULL;
				CaribouKeyModel* modifier = NULL;
				_tmp7_ = _g_object_ref0 (modifier_collection[modifier_it]);
				modifier = _tmp7_;
				{
					CaribouKeyModel* _tmp8_ = NULL;
					CaribouModifierState _tmp9_ = 0;
					_tmp8_ = modifier;
					_tmp9_ = _tmp8_->modifier_state;
					if (_tmp9_ == CARIBOU_MODIFIER_STATE_LATCHED) {
						CaribouKeyModel* _tmp10_ = NULL;
						CaribouKeyModel* _tmp11_ = NULL;
						_tmp10_ = modifier;
						_tmp10_->modifier_state = CARIBOU_MODIFIER_STATE_NONE;
						_tmp11_ = modifier;
						caribou_key_model_release (_tmp11_);
					}
					_g_object_unref0 (modifier);
				}
			}
		}
		modifiers = (_vala_array_free (modifiers, modifiers_length1, (GDestroyNotify) g_object_unref), NULL);
	}
}
