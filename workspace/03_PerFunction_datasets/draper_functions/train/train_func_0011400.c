multi_map_tests_construct (GType object_type, const gchar* name) {
	MultiMapTests * self = NULL;
	const gchar* _tmp0_ = NULL;
	g_return_val_if_fail (name != NULL, NULL);
	_tmp0_ = name;
	self = (MultiMapTests*) gee_test_case_construct (object_type, _tmp0_);
	gee_test_case_add_test ((GeeTestCase*) self, "[MultiMap] size", _multi_map_tests_test_size_gee_test_case_test_method, self);
	gee_test_case_add_test ((GeeTestCase*) self, "[MultiMap] getting and setting", _multi_map_tests_test_getting_setting_gee_test_case_test_method, self);
	gee_test_case_add_test ((GeeTestCase*) self, "[MultiMap] keys, all keys and values", _multi_map_tests_test_keys_all_keys_values_gee_test_case_test_method, self);
	return self;
}
