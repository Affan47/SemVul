__lambda2_ (Block1Data* _data1_, GObject* o, GAsyncResult* r) {
	PersonaStoreTests * self;
	GAsyncResult* _tmp0_ = NULL;
#line 73 "/home/treitter/collabora/folks/tests/eds/persona-store-tests.vala"
	self = _data1_->self;
#line 73 "/home/treitter/collabora/folks/tests/eds/persona-store-tests.vala"
	g_return_if_fail (r != NULL);
#line 75 "/home/treitter/collabora/folks/tests/eds/persona-store-tests.vala"
	_tmp0_ = r;
#line 75 "/home/treitter/collabora/folks/tests/eds/persona-store-tests.vala"
	folks_backend_store_prepare_finish (_data1_->backend_store, _tmp0_);
#line 247 "persona-store-tests.c"
}
