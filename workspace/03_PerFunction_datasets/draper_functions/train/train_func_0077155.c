unity_internal_scope_channel_owner_watcher_owner_changed (UnityInternalScopeChannelOwnerWatcher* self, GDBusConnection* con, const gchar* sender_name, const gchar* obj_path, const gchar* ifc_name, const gchar* sig_name, GVariant* parameters) {
	gchar* new_owner = NULL;
	GVariant* _tmp0_ = NULL;
	GVariant* _tmp1_ = NULL;
	GVariant* _tmp2_ = NULL;
	const gchar* _tmp3_ = NULL;
	gchar* _tmp4_ = NULL;
	gchar* _tmp5_ = NULL;
	const gchar* _tmp6_ = NULL;
	g_return_if_fail (self != NULL);
	g_return_if_fail (con != NULL);
	g_return_if_fail (sender_name != NULL);
	g_return_if_fail (obj_path != NULL);
	g_return_if_fail (ifc_name != NULL);
	g_return_if_fail (sig_name != NULL);
	g_return_if_fail (parameters != NULL);
	_tmp0_ = parameters;
	_tmp1_ = g_variant_get_child_value (_tmp0_, (gsize) 2);
	_tmp2_ = _tmp1_;
	_tmp3_ = g_variant_get_string (_tmp2_, NULL);
	_tmp4_ = g_strdup (_tmp3_);
	_tmp5_ = _tmp4_;
	_g_variant_unref0 (_tmp2_);
	new_owner = _tmp5_;
	_tmp6_ = new_owner;
	if (g_strcmp0 (_tmp6_, "") == 0) {
		UnityInternalScopeChannel* _tmp7_ = NULL;
		_tmp7_ = self->priv->owner_channel;
		g_signal_emit_by_name (_tmp7_, "owner-lost");
	}
	_g_free0 (new_owner);
}
