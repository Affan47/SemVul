test_types_script (void)
{
  hb_tag_t arab = HB_TAG_CHAR4 ("arab");
  hb_tag_t Arab = HB_TAG_CHAR4 ("Arab");
  hb_tag_t ARAB = HB_TAG_CHAR4 ("ARAB");

  hb_tag_t wWyZ = HB_TAG_CHAR4 ("wWyZ");
  hb_tag_t Wwyz = HB_TAG_CHAR4 ("Wwyz");

  hb_tag_t x123 = HB_TAG_CHAR4 ("x123");

  g_assert_cmpint (HB_SCRIPT_INVALID, ==, (hb_script_t) HB_TAG_NONE);
  g_assert_cmphex (HB_SCRIPT_ARABIC, !=, HB_SCRIPT_LATIN);

  g_assert_cmphex (HB_SCRIPT_INVALID, ==, hb_script_from_string (NULL, -1));
  g_assert_cmphex (HB_SCRIPT_INVALID, ==, hb_script_from_string ("", -1));
  g_assert_cmphex (HB_SCRIPT_INVALID, ==, hb_script_from_string ("x", 0));
  g_assert_cmphex (HB_SCRIPT_UNKNOWN, ==, hb_script_from_string ("x", -1));

  g_assert_cmphex (HB_SCRIPT_ARABIC, ==, hb_script_from_string ("arab", -1));
  g_assert_cmphex (HB_SCRIPT_ARABIC, ==, hb_script_from_string ("Arab", -1));
  g_assert_cmphex (HB_SCRIPT_ARABIC, ==, hb_script_from_string ("ARAB", -1));
  g_assert_cmphex (HB_SCRIPT_ARABIC, ==, hb_script_from_string ("Arabic", 6));
  g_assert_cmphex (HB_SCRIPT_ARABIC, !=, hb_script_from_string ("Arabic", 3));

  g_assert_cmphex (HB_SCRIPT_ARABIC, ==, hb_script_from_iso15924_tag (arab));
  g_assert_cmphex (HB_SCRIPT_ARABIC, ==, hb_script_from_iso15924_tag (Arab));
  g_assert_cmphex (HB_SCRIPT_ARABIC, ==, hb_script_from_iso15924_tag (ARAB));


  g_assert_cmphex (HB_SCRIPT_UNKNOWN, !=, hb_script_from_string ("wWyZ", -1));
  g_assert_cmphex (HB_SCRIPT_UNKNOWN, !=, hb_script_from_iso15924_tag (wWyZ));

  g_assert_cmphex (HB_SCRIPT_UNKNOWN, ==, hb_script_from_string ("x123", -1));
  g_assert_cmphex (HB_SCRIPT_UNKNOWN, ==, hb_script_from_iso15924_tag (x123));

  g_assert_cmphex (hb_script_to_iso15924_tag (HB_SCRIPT_ARABIC), ==, Arab);
  g_assert_cmphex (hb_script_to_iso15924_tag (hb_script_from_iso15924_tag (wWyZ)), ==, Wwyz);

  g_assert_cmpint (hb_script_get_horizontal_direction (HB_SCRIPT_LATIN), ==, HB_DIRECTION_LTR);
  g_assert_cmpint (hb_script_get_horizontal_direction (HB_SCRIPT_ARABIC), ==, HB_DIRECTION_RTL);
  g_assert_cmpint (hb_script_get_horizontal_direction (hb_script_from_iso15924_tag (wWyZ)), ==, HB_DIRECTION_LTR);
}
