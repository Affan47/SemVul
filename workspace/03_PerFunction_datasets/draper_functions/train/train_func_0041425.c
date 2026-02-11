test_parse_and_format (gconstpointer data)
{
	const ParseAndFormatData *const test_data = data;
	GError *error = NULL;
	EPhoneNumber *parsed;

	parsed = e_phone_number_from_string (
		test_data->phone_number, test_data->region_code, &error);

#ifdef ENABLE_PHONENUMBER

	{
		EPhoneNumberCountrySource source;
		gchar *national;
		gint i;

		g_assert_cmpint (
			e_phone_number_get_country_code (parsed, &source), ==,
			test_data->country_code);
		g_assert_cmpuint (source, ==, test_data->country_source);

		national = e_phone_number_get_national_number (parsed);
		g_assert_cmpstr (national, ==, test_data->national_number);
		g_free (national);

		g_assert (parsed != NULL);
		g_assert (error == NULL);

		for (i = 0; i < G_N_ELEMENTS (test_data->formatted_numbers); ++i) {
			gchar *formatted = e_phone_number_to_string (parsed, i);
			g_assert (formatted != NULL);
			g_assert_cmpstr (formatted, ==, test_data->formatted_numbers[i]);
			g_free (formatted);
		}

		e_phone_number_free (parsed);
	}

#else

	g_assert (parsed == NULL);
	g_assert (error != NULL);
	g_assert (error->domain == E_PHONE_NUMBER_ERROR);
	g_assert (error->code == E_PHONE_NUMBER_ERROR_NOT_IMPLEMENTED);
	g_assert (error->message != NULL);

#endif

	g_clear_error (&error);
}
