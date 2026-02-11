__lambda6_ (DataHub* self, GDBusConnection* conn) {
	GDBusConnection* _tmp0_ = NULL;
	GError * _inner_error_ = NULL;
	g_return_if_fail (conn != NULL);
	_tmp0_ = conn;
	data_hub_service_register_object (G_TYPE_CHECK_INSTANCE_CAST (self, TYPE_DATA_HUB_SERVICE, DataHubService), _tmp0_, DATA_HUB_OBJECT_PATH, &_inner_error_);
	if (_inner_error_ != NULL) {
		g_critical ("file %s: line %d: uncaught error: %s (%s, %d)", __FILE__, __LINE__, _inner_error_->message, g_quark_to_string (_inner_error_->domain), _inner_error_->code);
		g_clear_error (&_inner_error_);
		return;
	}
}
