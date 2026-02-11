validate_opt (const char *detail,
              GHashTable *hash,
              const char *key,
              OptType val_type,
              gconstpointer expected,
              size_t expected_len)
{
	GValue *value;
	gint int_val;
	GByteArray *array;
	const char *s;
	const unsigned char *expected_array = expected;
	int result;

	ASSERT (hash != NULL, detail, "hash was NULL");

	value = g_hash_table_lookup (hash, key);
	ASSERT (value != NULL,
	        detail, "option '%s' expected but not found in config hash.");

	switch (val_type) {
	case TYPE_INT:
		ASSERT (G_VALUE_HOLDS_INT (value),
		        detail, "config hash item '%s' was not TYPE_INT.", key);
		int_val = g_value_get_int (value);
		ASSERT (int_val == GPOINTER_TO_INT (expected),
		        detail, "unexpected config hash item '%s' value %d (expected %d)",
		        key, int_val, GPOINTER_TO_INT (expected));
		break;
	case TYPE_BYTES:
		ASSERT (G_VALUE_HOLDS (value, DBUS_TYPE_G_UCHAR_ARRAY),
		        detail, "config hash item '%s' was not TYPE_BYTES.", key);
		array = g_value_get_boxed (value);
		ASSERT (array->len == expected_len,
		        detail, "unexpected config hash item '%s' length %d (expected %d)",
		        key, array->len, expected_len);
		result = memcmp (array->data, expected_array, expected_len);
		ASSERT (result == 0, detail, "unexpected config hash item '%s' value", key);
		break;
	case TYPE_KEYWORD:
	case TYPE_STRING:
		ASSERT (G_VALUE_HOLDS_STRING (value),
		        detail, "config hash item '%s' was not TYPE_STRING or TYPE_KEYWORD.", key);
		if (expected_len == -1)
			expected_len = strlen ((const char *) expected);
		s = g_value_get_string (value);
		ASSERT (s != NULL, detail, "unexpected NULL config hash string item '%s'.", key);
		ASSERT (strlen (s) == expected_len,
		        detail, "unexpected config hash string item '%s' length %d (expected %d)",
		        key, strlen (s), expected_len);
		result = strcmp (s, (const char *) expected);
		ASSERT (result == 0,
		        detail, "unexpected config hash string item '%s' value '%s' (expected '%s')",
		        key, s, (const char *) expected);
		break;
	default:
		g_warning ("unknown supplicant config hash item '%s' option type %d",
		           key, val_type);
		return FALSE;
	}

	return TRUE;
}
