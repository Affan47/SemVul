kf_test_test_case_construct (GType object_type, const gchar* name) {
	KfTestTestCase * self = NULL;
	const gchar* _tmp0_ = NULL;
	KfTestBackend* _tmp1_ = NULL;
#line 41 "/home/treitter/collabora/folks/tests/lib/key-file/test-case.vala"
	g_return_val_if_fail (name != NULL, NULL);
#line 43 "/home/treitter/collabora/folks/tests/lib/key-file/test-case.vala"
	_tmp0_ = name;
#line 43 "/home/treitter/collabora/folks/tests/lib/key-file/test-case.vala"
	self = (KfTestTestCase*) folks_test_case_construct (object_type, _tmp0_);
#line 45 "/home/treitter/collabora/folks/tests/lib/key-file/test-case.vala"
	_tmp1_ = kf_test_backend_new ();
#line 45 "/home/treitter/collabora/folks/tests/lib/key-file/test-case.vala"
	_kf_test_backend_unref0 (self->kf_backend);
#line 45 "/home/treitter/collabora/folks/tests/lib/key-file/test-case.vala"
	self->kf_backend = _tmp1_;
#line 47 "/home/treitter/collabora/folks/tests/lib/key-file/test-case.vala"
	g_setenv ("FOLKS_BACKENDS_ALLOWED", "key-file", TRUE);
#line 48 "/home/treitter/collabora/folks/tests/lib/key-file/test-case.vala"
	g_setenv ("FOLKS_PRIMARY_STORE", "key-file", TRUE);
#line 41 "/home/treitter/collabora/folks/tests/lib/key-file/test-case.vala"
	return self;
#line 109 "test-case.c"
}
