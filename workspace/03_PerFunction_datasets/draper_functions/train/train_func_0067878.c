test_keyname (void)
{
    g_assert_cmpstr (ibus_keyval_name (IBUS_KEY_Home), ==, "Home");
    g_assert (ibus_keyval_from_name ("Home") == IBUS_KEY_Home);
}
