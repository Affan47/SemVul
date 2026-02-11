panel_bind_switch_shortcut (Panel* self) {
	gboolean _tmp0_ = FALSE;
	gchar** accelerators = NULL;
	GSettings* _tmp1_ = NULL;
	gchar** _tmp2_ = NULL;
	gchar** _tmp3_ = NULL;
	gint accelerators_length1 = 0;
	gint _accelerators_size_ = 0;
	KeybindingManager* keybinding_manager = NULL;
	KeybindingManager* _tmp4_ = NULL;
	gchar** _tmp5_ = NULL;
	gint _tmp5__length1 = 0;
	g_return_if_fail (self != NULL);
	_tmp0_ = panel_is_unity (self);
	if (_tmp0_) {
		return;
	}
	_tmp1_ = self->priv->m_settings_hotkey;
	_tmp3_ = _tmp2_ = g_settings_get_strv (_tmp1_, "triggers");
	accelerators = _tmp3_;
	accelerators_length1 = _vala_array_length (_tmp2_);
	_accelerators_size_ = accelerators_length1;
	_tmp4_ = keybinding_manager_get_instance ();
	keybinding_manager = _tmp4_;
	_tmp5_ = accelerators;
	_tmp5__length1 = accelerators_length1;
	{
		gchar** accelerator_collection = NULL;
		gint accelerator_collection_length1 = 0;
		gint _accelerator_collection_size_ = 0;
		gint accelerator_it = 0;
		accelerator_collection = _tmp5_;
		accelerator_collection_length1 = _tmp5__length1;
		for (accelerator_it = 0; accelerator_it < _tmp5__length1; accelerator_it = accelerator_it + 1) {
			gchar* _tmp6_ = NULL;
			gchar* accelerator = NULL;
			_tmp6_ = g_strdup (accelerator_collection[accelerator_it]);
			accelerator = _tmp6_;
			{
				KeybindingManager* _tmp7_ = NULL;
				const gchar* _tmp8_ = NULL;
				_tmp7_ = keybinding_manager;
				_tmp8_ = accelerator;
				panel_keybinding_manager_bind (self, _tmp7_, _tmp8_);
				_g_free0 (accelerator);
			}
		}
	}
	_g_object_unref0 (keybinding_manager);
	accelerators = (_vala_array_free (accelerators, accelerators_length1, (GDestroyNotify) g_free), NULL);
}
