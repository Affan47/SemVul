test_attributes_empty (void)
{
	GckBuilder builder = GCK_BUILDER_INIT;
	GckAttributes *attrs;
	const GckAttribute *attr;
	guint i;

	gck_builder_add_empty (&builder, 101UL);
	gck_builder_add_empty (&builder, 202UL);
	gck_builder_add_empty (&builder, 303UL);
	gck_builder_add_empty (&builder, 404UL);
	attrs = gck_builder_end (&builder);

	g_assert_cmpuint (gck_attributes_count (attrs), ==, 4);
	for (i = 0; i < gck_attributes_count (attrs); ++i) {
		attr = gck_attributes_at (attrs, i);
		g_assert (attr->type == ((i + 1) * 100) + i + 1);
		g_assert (attr->value == NULL);
		g_assert (attr->length == 0);
	}

	gck_attributes_unref (attrs);
}
