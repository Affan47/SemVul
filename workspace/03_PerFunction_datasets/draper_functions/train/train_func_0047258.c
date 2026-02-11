settings_manager_constructor (GType type, guint n_construct_properties, GObjectConstructParam * construct_properties) {
	GObject * obj;
	GObjectClass * parent_class;
	SettingsManager * self;
	GSettings* _tmp0_ = NULL;
	GSettings* _tmp1_ = NULL;
	GSettings* _tmp2_ = NULL;
	parent_class = G_OBJECT_CLASS (settings_manager_parent_class);
	obj = parent_class->constructor (type, n_construct_properties, construct_properties);
	self = G_TYPE_CHECK_INSTANCE_CAST (obj, TYPE_SETTINGS_MANAGER, SettingsManager);
	_tmp0_ = g_settings_new ("com.canonical.indicator.sound");
	_g_object_unref0 (self->priv->settings);
	self->priv->settings = _tmp0_;
	_tmp1_ = self->priv->settings;
	g_signal_connect_object (_tmp1_, "changed::blacklisted-media-players", (GCallback) _settings_manager_on_blacklist_event_g_settings_changed, self, 0);
	_tmp2_ = self->priv->settings;
	g_signal_connect_object (_tmp2_, "changed::preferred-media-players", (GCallback) _settings_manager_on_preferred_event_g_settings_changed, self, 0);
	return obj;
}
