test_new_string (void)
{
	GckAttribute *attr;

	attr = gck_attribute_new_string (ATTR_TYPE, "a test string");
	g_assert (attr->type == ATTR_TYPE);
	g_assert (attr->length == strlen ("a test string"));
	g_assert (memcmp (attr->value, "a test string", attr->length) == 0);

	gck_attribute_free (attr);
}
