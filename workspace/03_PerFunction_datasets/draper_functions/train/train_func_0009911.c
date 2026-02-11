backend_loading_tests_test_reloading (BackendLoadingTests* self) {
	GMainLoop* _tmp0_ = NULL;
	FolksBackendStore* store = NULL;
	FolksBackendStore* _tmp1_ = NULL;
	GMainLoop* _tmp2_ = NULL;
#line 157 "/home/treitter/collabora/folks/tests/folks/backend-loading.vala"
	g_return_if_fail (self != NULL);
#line 159 "/home/treitter/collabora/folks/tests/folks/backend-loading.vala"
	_tmp0_ = g_main_loop_new (NULL, FALSE);
#line 159 "/home/treitter/collabora/folks/tests/folks/backend-loading.vala"
	_g_main_loop_unref0 (self->priv->main_loop);
#line 159 "/home/treitter/collabora/folks/tests/folks/backend-loading.vala"
	self->priv->main_loop = _tmp0_;
#line 161 "/home/treitter/collabora/folks/tests/folks/backend-loading.vala"
	_tmp1_ = folks_backend_store_dup ();
#line 161 "/home/treitter/collabora/folks/tests/folks/backend-loading.vala"
	store = _tmp1_;
#line 162 "/home/treitter/collabora/folks/tests/folks/backend-loading.vala"
	backend_loading_tests_test_reloading_async (self, store, ___lambda5__gasync_ready_callback, g_object_ref (self));
#line 167 "/home/treitter/collabora/folks/tests/folks/backend-loading.vala"
	_tmp2_ = self->priv->main_loop;
#line 167 "/home/treitter/collabora/folks/tests/folks/backend-loading.vala"
	g_main_loop_run (_tmp2_);
#line 157 "/home/treitter/collabora/folks/tests/folks/backend-loading.vala"
	_g_object_unref0 (store);
#line 1210 "backend-loading.c"
}
