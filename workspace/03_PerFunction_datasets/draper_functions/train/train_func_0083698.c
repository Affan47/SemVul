test_new_invalid (void)
{
	GckAttribute *attr;

	attr = gck_attribute_new_invalid (ATTR_TYPE);
	g_assert (attr->type == ATTR_TYPE);
	g_assert (attr->length == (gulong)-1);
	g_assert (attr->value == NULL);

	g_assert (gck_attribute_is_invalid (attr));

	gck_attribute_free (attr);
}
