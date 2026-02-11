__lambda4_ (AvatarCacheTests* self, GObject* object, GAsyncResult* _result_) {
	GAsyncResult* _tmp0_ = NULL;
	gboolean _tmp1_ = FALSE;
	GMainLoop* _tmp2_ = NULL;
#line 181 "/home/treitter/collabora/folks/tests/folks/avatar-cache.vala"
	g_return_if_fail (_result_ != NULL);
#line 183 "/home/treitter/collabora/folks/tests/folks/avatar-cache.vala"
	_tmp0_ = _result_;
#line 183 "/home/treitter/collabora/folks/tests/folks/avatar-cache.vala"
	_tmp1_ = folks_test_utils_loadable_icons_content_equal_finish (_tmp0_);
#line 183 "/home/treitter/collabora/folks/tests/folks/avatar-cache.vala"
	_vala_assert (_tmp1_, "TestUtils.loadable_icons_content_equal.end (result)");
#line 184 "/home/treitter/collabora/folks/tests/folks/avatar-cache.vala"
	_tmp2_ = self->priv->_main_loop;
#line 184 "/home/treitter/collabora/folks/tests/folks/avatar-cache.vala"
	g_main_loop_quit (_tmp2_);
#line 880 "avatar-cache.c"
}
