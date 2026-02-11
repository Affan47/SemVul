test_build_take (void)
{
	GckBuilder builder = GCK_BUILDER_INIT;
	GckAttributes *attrs;
	const GckAttribute *attr;
	guchar *memory;

	memory = g_memdup (ATTR_DATA, N_ATTR_DATA);
	gck_builder_take_data (&builder, ATTR_TYPE, memory, N_ATTR_DATA);
	attrs = gck_builder_end (&builder);

	attr = gck_attributes_at (attrs, 0);

	g_assert (attr->type == ATTR_TYPE);
	g_assert (attr->length == N_ATTR_DATA);
	g_assert (memcmp (attr->value, ATTR_DATA, attr->length) == 0);

	gck_attributes_unref (attrs);
}
