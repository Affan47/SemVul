test_copy_attribute (void)
{
	GckAttribute attr, copy;

	gck_attribute_init_ulong (&attr, ATTR_TYPE, 88);
	gck_attribute_init_copy (&copy, &attr);
	gck_attribute_clear (&attr);
	g_assert (gck_attribute_get_ulong (&copy) == 88);
	g_assert (copy.type == ATTR_TYPE);
	gck_attribute_clear (&copy);
}
