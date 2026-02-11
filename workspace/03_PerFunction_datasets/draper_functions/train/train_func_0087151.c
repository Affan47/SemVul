test_set_get_value (TestPin        *test,
                    gconstpointer   data)
{
  const guchar *value;
  gsize n_value = G_MAXSIZE;

  value = g_tls_password_get_value (test->pin, &n_value);
  g_assert_cmpuint (n_value, ==, 0);
  g_assert (value == NULL);

  g_tls_password_set_value (test->pin, (const guchar *)"secret", -1);

  value = g_tls_password_get_value (test->pin, &n_value);
  g_assert_cmpuint (n_value, ==, 6);
  g_assert (!strncmp ((const gchar *)value, "secret", n_value));

  g_tls_password_set_value (test->pin, (const guchar *)"other", 5);

  value = g_tls_password_get_value (test->pin, &n_value);
  g_assert_cmpuint (n_value, ==, 5);
  g_assert (!strncmp ((const gchar *)value, "other", n_value));
}
