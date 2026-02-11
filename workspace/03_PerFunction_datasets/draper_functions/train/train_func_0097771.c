fso_gsm_at_channel_finalize (GObject* obj) {
	FsoGsmAtChannel * self;
	self = G_TYPE_CHECK_INSTANCE_CAST (obj, FSO_GSM_TYPE_AT_CHANNEL, FsoGsmAtChannel);
	_g_free0 (self->name);
	_g_object_unref0 (self->priv->modem);
	G_OBJECT_CLASS (fso_gsm_at_channel_parent_class)->finalize (obj);
}
