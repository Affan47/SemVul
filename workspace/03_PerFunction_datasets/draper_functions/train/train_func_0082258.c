get_pincode_for_device (guint type, const char *address, const char *name, guint *max_digits)
{
	GMarkupParseContext *ctx;
	GMarkupParser parser = { pin_db_parse_start_tag, NULL, NULL, NULL, NULL };
	PinParseData data;
	char *buf;
	gsize buf_len;
	GError *err = NULL;

	g_return_val_if_fail (address != NULL, NULL);

	g_debug ("Getting pincode for device '%s' (type: %s address: %s)",
		 name ? name : "", address, bluetooth_type_to_string (type));


	if (!g_file_get_contents(PIN_CODE_DB, &buf, &buf_len, NULL)) {
		char *filename;

		filename = g_build_filename(PKGDATADIR, PIN_CODE_DB, NULL);
		if (!g_file_get_contents(filename, &buf, &buf_len, NULL)) {
			g_warning("Could not load "PIN_CODE_DB);
			g_free (filename);
			return NULL;
		}
		g_free (filename);
	}

	data.ret_pin = NULL;
	data.max_digits = 0;
	data.type = type;
	data.address = address;
	data.name = name;

	ctx = g_markup_parse_context_new (&parser, 0, &data, NULL);

	if (!g_markup_parse_context_parse (ctx, buf, buf_len, &err)) {
		g_warning ("Failed to parse '%s': %s\n", PIN_CODE_DB, err->message);
		g_error_free (err);
	}

	g_markup_parse_context_free (ctx);
	g_free (buf);

	if (max_digits != NULL)
		*max_digits = data.max_digits;

	g_debug ("Got pin '%s' (max digits: %d) for device '%s' (type: %s address: %s)",
		 data.ret_pin, data.max_digits,
		 name ? name : "", address, bluetooth_type_to_string (type));

	return data.ret_pin;
}
