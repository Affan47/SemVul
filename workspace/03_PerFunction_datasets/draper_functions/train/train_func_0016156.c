test_attribute_contains_no_value (void)
{
	CK_ATTRIBUTE attr = { CKA_ID, "other-identifier", 16 };
	gboolean ret;

	ret = gkm_attributes_contains (attr_template, G_N_ELEMENTS (attr_template), &attr);
	g_assert (ret == FALSE);
}
