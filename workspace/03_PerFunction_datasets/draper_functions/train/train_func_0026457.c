test_build_data (void)
{
	GckBuilder builder = GCK_BUILDER_INIT;
	GckAttributes *attrs;
	const GckAttribute *attr;

	gck_builder_add_data (&builder, ATTR_TYPE, (const guchar *)"Hello", 5);
	attr = gck_builder_find (&builder, ATTR_TYPE);
	g_assert (attr->type == ATTR_TYPE);
	g_assert (attr->length == 5);
	g_assert (memcmp (attr->value, "Hello", attr->length) == 0);

	gck_builder_set_data (&builder, ATTR_TYPE, (const guchar *)ATTR_DATA, N_ATTR_DATA);
	g_assert (attr->type == ATTR_TYPE);
	g_assert (attr->length == N_ATTR_DATA);
	g_assert (memcmp (attr->value, ATTR_DATA, attr->length) == 0);

	attrs = gck_builder_end (&builder);
	attr = gck_attributes_at (attrs, 0);
	g_assert (attr->type == ATTR_TYPE);
	g_assert (attr->length == N_ATTR_DATA);
	g_assert (memcmp (attr->value, ATTR_DATA, attr->length) == 0);

	gck_attributes_unref (attrs);
}
