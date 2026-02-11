array_length_resolve(testString)
	 char            *testString;
{
	int             counter = 0;
	char            *array_name = &testString[1];

	struct integer_type *integer_pointer = integer_table;
	struct cinteger_type *cinteger_pointer = cinteger_table;
	struct string_type *string_pointer = string_table;
	struct string_type *cstring_pointer = cstring_table;

	if (integer_pointer != NULL) {
		do {
			if (!strcmp(array_name, integer_pointer->name)) {
				counter++;
			}
			integer_pointer = integer_pointer->next_integer;
		}
		while (integer_pointer != NULL);
	}


	if (counter)
		return (counter);

	if (string_pointer != NULL) {
		do {
			if (!strcmp(array_name, string_pointer->name)) {
				counter++;
			}
			string_pointer = string_pointer->next_string;
		}
		while (string_pointer != NULL);
	}


	if (counter)
		return (counter);

	if (cinteger_pointer != NULL) {
		do {
			if (!strcmp(array_name, cinteger_pointer->name)) {
				counter++;
			}
			cinteger_pointer = cinteger_pointer->next_cinteger;
		}
		while (cinteger_pointer != NULL);
	}


	if (counter)
		return (counter);

	if (cstring_pointer != NULL) {
		do {
			if (!strcmp(array_name, cstring_pointer->name)) {
				counter++;
			}
			cstring_pointer = cstring_pointer->next_string;
		}
		while (cstring_pointer != NULL);
	}


	if (counter)
		return (counter);


	return (0);
}
