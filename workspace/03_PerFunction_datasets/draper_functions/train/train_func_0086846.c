test_gd_phone_number_comparison (void)
{
	GDataGDPhoneNumber *phone1, *phone2;


	phone1 = gdata_gd_phone_number_new ("123", NULL, NULL, "phone://123", TRUE);
	phone2 = gdata_gd_phone_number_new ("123", NULL, "label", "phone://123", FALSE);
	g_assert_cmpint (gdata_comparable_compare (GDATA_COMPARABLE (phone1), GDATA_COMPARABLE (phone2)), ==, 0);


	gdata_gd_phone_number_set_uri (phone1, "phone://+44123");
	g_assert_cmpint (gdata_comparable_compare (GDATA_COMPARABLE (phone1), GDATA_COMPARABLE (phone2)), ==, 0);


	gdata_gd_phone_number_set_uri (phone1, "phone://123");
	gdata_gd_phone_number_set_number (phone1, "+44123");
	g_assert_cmpint (gdata_comparable_compare (GDATA_COMPARABLE (phone1), GDATA_COMPARABLE (phone2)), ==, 0);


	gdata_gd_phone_number_set_number (phone1, "456");
	gdata_gd_phone_number_set_uri (phone1, "phone://456");
	g_assert_cmpint (gdata_comparable_compare (GDATA_COMPARABLE (phone1), GDATA_COMPARABLE (phone2)), !=, 0);


	gdata_gd_phone_number_set_uri (phone1, NULL);
	gdata_gd_phone_number_set_uri (phone2, NULL);
	g_assert_cmpint (gdata_comparable_compare (GDATA_COMPARABLE (phone1), GDATA_COMPARABLE (phone2)), !=, 0);


	gdata_gd_phone_number_set_number (phone1, "123");
	g_assert_cmpint (gdata_comparable_compare (GDATA_COMPARABLE (phone1), GDATA_COMPARABLE (phone2)), ==, 0);

	g_object_unref (phone2);
	g_object_unref (phone1);
}
