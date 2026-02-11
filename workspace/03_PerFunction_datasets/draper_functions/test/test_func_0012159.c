_folks_test_case_log_adaptor_log_func_stack_trace (const gchar* log_domain, GLogLevelFlags log_levels, const gchar* message) {
	GLogFunc _tmp0_ = NULL;
	void* _tmp0__target = NULL;
	const gchar* _tmp1_ = NULL;
	GLogLevelFlags _tmp2_ = 0;
	const gchar* _tmp3_ = NULL;
	GLogLevelFlags _tmp4_ = 0;
#line 327 "/home/treitter/collabora/folks/tests/lib/test-case.vala"
	g_return_if_fail (message != NULL);
#line 331 "/home/treitter/collabora/folks/tests/lib/test-case.vala"
	_tmp0_ = g_log_default_handler;
#line 331 "/home/treitter/collabora/folks/tests/lib/test-case.vala"
	_tmp0__target = NULL;
#line 331 "/home/treitter/collabora/folks/tests/lib/test-case.vala"
	_tmp1_ = log_domain;
#line 331 "/home/treitter/collabora/folks/tests/lib/test-case.vala"
	_tmp2_ = log_levels;
#line 331 "/home/treitter/collabora/folks/tests/lib/test-case.vala"
	_tmp3_ = message;
#line 331 "/home/treitter/collabora/folks/tests/lib/test-case.vala"
	_tmp0_ (_tmp1_, _tmp2_, _tmp3_, _tmp0__target);
#line 335 "/home/treitter/collabora/folks/tests/lib/test-case.vala"
	_tmp4_ = log_levels;
#line 335 "/home/treitter/collabora/folks/tests/lib/test-case.vala"
	if ((_tmp4_ & ((G_LOG_LEVEL_WARNING | G_LOG_LEVEL_ERROR) | G_LOG_LEVEL_CRITICAL)) != 0) {
#line 340 "/home/treitter/collabora/folks/tests/lib/test-case.vala"
		g_on_error_stack_trace ("libtool --mode=execute gdb");
#line 984 "test-case.c"
	}
}
