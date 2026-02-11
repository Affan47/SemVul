check_double_value (GKeyFile    *keyfile,
		    const gchar *group,
		    const gchar *key,
		    gdouble      expected)
{
  GError *error = NULL;
  gdouble value;
  value = g_key_file_get_double (keyfile, group, key, &error);
  check_no_error (error);
  cut_assert_equal_double (expected, 0.0, value,
		  	   cut_message ("Group %s key %s: "
                                        "expected integer value %e, "
                                        "actual value %e",
                                        group, key, expected, value));
}
