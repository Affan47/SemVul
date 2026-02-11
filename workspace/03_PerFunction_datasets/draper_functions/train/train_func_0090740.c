test_get_name (PidginTestCaseFixture *fixture,
    gconstpointer user_data)
{
  const gchar *name;

  name = _tpl_log_store_get_name (TPL_LOG_STORE (fixture->store));

  g_assert_cmpstr (name, ==, "Pidgin");
}
