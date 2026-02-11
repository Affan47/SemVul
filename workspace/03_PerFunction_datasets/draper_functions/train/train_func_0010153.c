indicator_keyboard_ibus_menu_construct (GType object_type, GActionMap* action_map, IBusPropList* properties) {
	IndicatorKeyboardIBusMenu * self = NULL;
	GMenu* _tmp0_ = NULL;
	GMenu* _tmp1_ = NULL;
	GeeLinkedList* _tmp2_ = NULL;
	GActionMap* _tmp3_ = NULL;
	IBusPropList* _tmp4_ = NULL;
	self = (IndicatorKeyboardIBusMenu*) g_object_new (object_type, NULL);
	_tmp0_ = g_menu_new ();
	_g_object_unref0 (self->priv->menu);
	self->priv->menu = _tmp0_;
	_tmp1_ = self->priv->menu;
	g_signal_connect_object ((GMenuModel*) _tmp1_, "items-changed", (GCallback) ___lambda3__g_menu_model_items_changed, self, 0);
	_tmp2_ = gee_linked_list_new (G_TYPE_STRING, (GBoxedCopyFunc) g_strdup, g_free, NULL);
	_g_object_unref0 (self->priv->names);
	self->priv->names = _tmp2_;
	_tmp3_ = action_map;
	indicator_keyboard_ibus_menu_set_action_map (self, _tmp3_);
	_tmp4_ = properties;
	indicator_keyboard_ibus_menu_set_properties (self, _tmp4_);
	return self;
}
