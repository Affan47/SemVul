_object_cache_tests_delete_cache_directory (ObjectCacheTests* self) {
	GError * _inner_error_ = NULL;
#line 137 "/home/treitter/collabora/folks/tests/folks/object-cache.vala"
	g_return_if_fail (self != NULL);
#line 1292 "object-cache.c"
	{
		GFile* _tmp0_ = NULL;
#line 141 "/home/treitter/collabora/folks/tests/folks/object-cache.vala"
		_tmp0_ = self->priv->_cache_dir;
#line 141 "/home/treitter/collabora/folks/tests/folks/object-cache.vala"
		_object_cache_tests_delete_directory (self, _tmp0_, &_inner_error_);
#line 141 "/home/treitter/collabora/folks/tests/folks/object-cache.vala"
		if (_inner_error_ != NULL) {
#line 1301 "object-cache.c"
			goto __catch0_g_error;
		}
	}
	goto __finally0;
	__catch0_g_error:
	{
		GError* e = NULL;
#line 139 "/home/treitter/collabora/folks/tests/folks/object-cache.vala"
		e = _inner_error_;
#line 139 "/home/treitter/collabora/folks/tests/folks/object-cache.vala"
		_inner_error_ = NULL;
#line 139 "/home/treitter/collabora/folks/tests/folks/object-cache.vala"
		_g_error_free0 (e);
#line 1315 "object-cache.c"
	}
	__finally0:
#line 139 "/home/treitter/collabora/folks/tests/folks/object-cache.vala"
	if (_inner_error_ != NULL) {
#line 139 "/home/treitter/collabora/folks/tests/folks/object-cache.vala"
		g_critical ("file %s: line %d: uncaught error: %s (%s, %d)", __FILE__, __LINE__, _inner_error_->message, g_quark_to_string (_inner_error_->domain), _inner_error_->code);
#line 139 "/home/treitter/collabora/folks/tests/folks/object-cache.vala"
		g_clear_error (&_inner_error_);
#line 139 "/home/treitter/collabora/folks/tests/folks/object-cache.vala"
		return;
#line 1326 "object-cache.c"
	}
}
