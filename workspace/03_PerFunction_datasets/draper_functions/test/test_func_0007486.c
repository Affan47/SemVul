folks_test_utils_get_built_test_data (const gchar* filename) {
	gchar* result = NULL;
	const gchar* _tmp0_ = NULL;
#line 327 "/home/treitter/collabora/folks/tests/lib/test-utils.vala"
	g_return_val_if_fail (filename != NULL, NULL);
#line 329 "/home/treitter/collabora/folks/tests/lib/test-utils.vala"
	_tmp0_ = g_getenv ("FOLKS_TESTS_INSTALLED");
#line 329 "/home/treitter/collabora/folks/tests/lib/test-utils.vala"
	if (_tmp0_ != NULL) {
#line 1938 "test-utils.c"
		const gchar* _tmp1_ = NULL;
		gchar* _tmp2_ = NULL;
#line 331 "/home/treitter/collabora/folks/tests/lib/test-utils.vala"
		_tmp1_ = filename;
#line 331 "/home/treitter/collabora/folks/tests/lib/test-utils.vala"
		_tmp2_ = g_strconcat (PACKAGE_DATADIR "/tests/", _tmp1_, NULL);
#line 331 "/home/treitter/collabora/folks/tests/lib/test-utils.vala"
		result = _tmp2_;
#line 331 "/home/treitter/collabora/folks/tests/lib/test-utils.vala"
		return result;
#line 1949 "test-utils.c"
	} else {
		const gchar* _tmp3_ = NULL;
		gchar* _tmp4_ = NULL;
#line 335 "/home/treitter/collabora/folks/tests/lib/test-utils.vala"
		_tmp3_ = filename;
#line 335 "/home/treitter/collabora/folks/tests/lib/test-utils.vala"
		_tmp4_ = g_strconcat (ABS_TOP_BUILDDIR "/tests/", _tmp3_, NULL);
#line 335 "/home/treitter/collabora/folks/tests/lib/test-utils.vala"
		result = _tmp4_;
#line 335 "/home/treitter/collabora/folks/tests/lib/test-utils.vala"
		return result;
#line 1961 "test-utils.c"
	}
}
