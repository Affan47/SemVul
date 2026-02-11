verify_cert (GByteArray *array, const char *prop_name, GError **error)
{
	if (!array)
		return TRUE;

	switch (get_cert_scheme (array)) {
	case NM_SETTING_802_1X_CK_SCHEME_BLOB:
		return TRUE;
	case NM_SETTING_802_1X_CK_SCHEME_PATH:

		if (array->data[array->len - 1] == '\0') {


			if (g_utf8_validate ((const char *) (array->data + strlen (SCHEME_PATH)), -1, NULL))
				return TRUE;
		}
		break;
	default:
		break;
	}

	g_set_error (error,
	             NM_SETTING_802_1X_ERROR,
	             NM_SETTING_802_1X_ERROR_INVALID_PROPERTY,
	             "%s", prop_name);
	return FALSE;
}
