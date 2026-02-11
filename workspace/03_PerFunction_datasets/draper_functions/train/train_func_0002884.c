value_take_test_object (GValue* value, gpointer v_object) {
	TestObject* old;
#line 5 "/home/treitter/collabora/folks/tests/folks/object-cache.vala"
	g_return_if_fail (G_TYPE_CHECK_VALUE_TYPE (value, TYPE_TEST_OBJECT));
#line 5 "/home/treitter/collabora/folks/tests/folks/object-cache.vala"
	old = value->data[0].v_pointer;
#line 5 "/home/treitter/collabora/folks/tests/folks/object-cache.vala"
	if (v_object) {
#line 5 "/home/treitter/collabora/folks/tests/folks/object-cache.vala"
		g_return_if_fail (G_TYPE_CHECK_INSTANCE_TYPE (v_object, TYPE_TEST_OBJECT));
#line 5 "/home/treitter/collabora/folks/tests/folks/object-cache.vala"
		g_return_if_fail (g_value_type_compatible (G_TYPE_FROM_INSTANCE (v_object), G_VALUE_TYPE (value)));
#line 5 "/home/treitter/collabora/folks/tests/folks/object-cache.vala"
		value->data[0].v_pointer = v_object;
#line 591 "object-cache.c"
	} else {
#line 5 "/home/treitter/collabora/folks/tests/folks/object-cache.vala"
		value->data[0].v_pointer = NULL;
#line 595 "object-cache.c"
	}
#line 5 "/home/treitter/collabora/folks/tests/folks/object-cache.vala"
	if (old) {
#line 5 "/home/treitter/collabora/folks/tests/folks/object-cache.vala"
		test_object_unref (old);
#line 601 "object-cache.c"
	}
}
