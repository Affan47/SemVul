diodon_main (gchar** args, int args_length1) {
	gint result = 0;
	GTestSuite* _tmp0_ = NULL;
	DiodonTestTextClipboardItem* _tmp1_ = NULL;
	DiodonTestTextClipboardItem* _tmp2_ = NULL;
	GTestSuite* _tmp3_ = NULL;
	gint _tmp4_ = 0;
	g_test_init (&args_length1, &args, NULL);
	_tmp0_ = g_test_get_root ();
	_tmp1_ = diodon_test_text_clipboard_item_new ();
	_tmp2_ = _tmp1_;
	_tmp3_ = diodon_test_case_get_suite ((DiodonTestCase*) _tmp2_);
	g_test_suite_add_suite (_tmp0_, _tmp3_);
	_g_object_unref0 (_tmp2_);
	_tmp4_ = g_test_run ();
	result = _tmp4_;
	return result;
}
