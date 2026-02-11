test_attributes (TestPin        *test,
                 gconstpointer   data)
{
  GTlsPasswordFlags flags;
  const gchar *description;

  flags = g_tls_password_get_flags (test->pin);
  g_assert_cmpuint (flags, ==, G_TLS_PASSWORD_RETRY);

  description = g_tls_password_get_description (test->pin);
  g_assert_cmpstr (description, ==, "Test description");
}
