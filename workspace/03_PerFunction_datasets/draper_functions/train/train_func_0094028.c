test_to_password_extra_ref (void)
{
	SecretValue *value;
	gchar *password;

	value = secret_value_new_full (egg_secure_strdup ("blah"), -1,
	                                "text/plain", egg_secure_free);
	secret_value_ref (value);

	password = _secret_value_unref_to_password (value);
	g_assert_cmpstr (password, ==, "blah");

	egg_secure_free (password);
	secret_value_unref (value);
}
