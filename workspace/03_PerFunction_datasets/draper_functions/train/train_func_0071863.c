________lambda3_ (Example* self, GObject* obj, GAsyncResult* res) {
	gchar* _tmp0_;
	gchar* _result_;
	FILE* _tmp6_;
	const gchar* _tmp7_;
	GError * _inner_error_ = NULL;
	g_return_if_fail (res != NULL);
	_tmp0_ = g_strdup ("");
	_result_ = _tmp0_;
	{
		FriendsDispatcher* _tmp1_;
		GAsyncResult* _tmp2_;
		gchar* _tmp3_ = NULL;
		_tmp1_ = self->dispatcher;
		_tmp2_ = res;
		friends_dispatcher_unlike_finish (_tmp1_, _tmp2_, &_tmp3_, &_inner_error_);
		_g_free0 (_result_);
		_result_ = _tmp3_;
		if (_inner_error_ != NULL) {
			if (_inner_error_->domain == G_IO_ERROR) {
				goto __catch4_g_io_error;
			}
			_g_free0 (_result_);
			g_critical ("file %s: line %d: unexpected error: %s (%s, %d)", __FILE__, __LINE__, _inner_error_->message, g_quark_to_string (_inner_error_->domain), _inner_error_->code);
			g_clear_error (&_inner_error_);
			return;
		}
	}
	goto __finally4;
	__catch4_g_io_error:
	{
		GError* e = NULL;
		GError* _tmp4_;
		const gchar* _tmp5_;
		e = _inner_error_;
		_inner_error_ = NULL;
		_tmp4_ = e;
		_tmp5_ = _tmp4_->message;
		g_warning ("example-vala.vala:115: %s", _tmp5_);
		_g_error_free0 (e);
	}
	__finally4:
	if (_inner_error_ != NULL) {
		_g_free0 (_result_);
		g_critical ("file %s: line %d: uncaught error: %s (%s, %d)", __FILE__, __LINE__, _inner_error_->message, g_quark_to_string (_inner_error_->domain), _inner_error_->code);
		g_clear_error (&_inner_error_);
		return;
	}
	_tmp6_ = stdout;
	_tmp7_ = _result_;
	fprintf (_tmp6_, "Unliked: %s\n", _tmp7_);
	self->waiting = FALSE;
	_g_free0 (_result_);
}
