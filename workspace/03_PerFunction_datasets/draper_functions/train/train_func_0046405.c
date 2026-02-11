test_get_string (void)
{
	GckAttribute *attr;
	gchar *value;

	attr = gck_attribute_new_string (ATTR_TYPE, "a test string");
	value = gck_attribute_get_string (attr);
	g_assert (strcmp ("a test string", value) == 0);
	g_free (value);
	gck_attribute_free (attr);


	attr = gck_attribute_new_string (ATTR_TYPE, NULL);
	value = gck_attribute_get_string (attr);
	g_assert (value == NULL);
	gck_attribute_free (attr);
}
