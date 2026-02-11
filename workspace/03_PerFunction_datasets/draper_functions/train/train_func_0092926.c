func_check_phone (struct _ESExp *f,
                  gint argc,
                  struct _ESExpResult **argv,
                  gpointer data)
{
	ESExpResult *const r = func_check (f, argc, argv, data);
	const gchar *const query_value = argv[1]->value.string;
	EPhoneNumber *number;


	if (!e_phone_number_is_supported ()) {
		r->value.number |= CHECK_UNSUPPORTED;
		return r;
	}

	number = e_phone_number_from_string (query_value, NULL, NULL);

	if (number == NULL) {


		r->value.number |= CHECK_INVALID;
	} else {
		e_phone_number_free (number);
	}

	return r;
}
