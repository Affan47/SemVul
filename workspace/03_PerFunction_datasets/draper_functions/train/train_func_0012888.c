folks_test_case_get_transient_dir (FolksTestCase* self) {
	const gchar* result;
	const gchar* _tmp0_ = NULL;
	const gchar* _tmp1_ = NULL;
#line 98 "/home/treitter/collabora/folks/tests/lib/test-case.vala"
	g_return_val_if_fail (self != NULL, NULL);
#line 100 "/home/treitter/collabora/folks/tests/lib/test-case.vala"
	_tmp0_ = self->priv->_transient_dir;
#line 100 "/home/treitter/collabora/folks/tests/lib/test-case.vala"
	_vala_assert (_tmp0_ != NULL, "this._transient_dir != null");
#line 101 "/home/treitter/collabora/folks/tests/lib/test-case.vala"
	_tmp1_ = self->priv->_transient_dir;
#line 101 "/home/treitter/collabora/folks/tests/lib/test-case.vala"
	result = (const gchar*) _tmp1_;
#line 101 "/home/treitter/collabora/folks/tests/lib/test-case.vala"
	return result;
#line 844 "test-case.c"
}
