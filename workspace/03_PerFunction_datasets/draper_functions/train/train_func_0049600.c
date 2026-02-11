folks_value_set_test_utils (GValue* value, gpointer v_object) {
	FolksTestUtils* old;
#line 26 "/home/treitter/collabora/folks/tests/lib/test-utils.vala"
	g_return_if_fail (G_TYPE_CHECK_VALUE_TYPE (value, FOLKS_TYPE_TEST_UTILS));
#line 26 "/home/treitter/collabora/folks/tests/lib/test-utils.vala"
	old = value->data[0].v_pointer;
#line 26 "/home/treitter/collabora/folks/tests/lib/test-utils.vala"
	if (v_object) {
#line 26 "/home/treitter/collabora/folks/tests/lib/test-utils.vala"
		g_return_if_fail (G_TYPE_CHECK_INSTANCE_TYPE (v_object, FOLKS_TYPE_TEST_UTILS));
#line 26 "/home/treitter/collabora/folks/tests/lib/test-utils.vala"
		g_return_if_fail (g_value_type_compatible (G_TYPE_FROM_INSTANCE (v_object), G_VALUE_TYPE (value)));
#line 26 "/home/treitter/collabora/folks/tests/lib/test-utils.vala"
		value->data[0].v_pointer = v_object;
#line 26 "/home/treitter/collabora/folks/tests/lib/test-utils.vala"
		folks_test_utils_ref (value->data[0].v_pointer);
#line 2119 "test-utils.c"
	} else {
#line 26 "/home/treitter/collabora/folks/tests/lib/test-utils.vala"
		value->data[0].v_pointer = NULL;
#line 2123 "test-utils.c"
	}
#line 26 "/home/treitter/collabora/folks/tests/lib/test-utils.vala"
	if (old) {
#line 26 "/home/treitter/collabora/folks/tests/lib/test-utils.vala"
		folks_test_utils_unref (old);
#line 2129 "test-utils.c"
	}
}
