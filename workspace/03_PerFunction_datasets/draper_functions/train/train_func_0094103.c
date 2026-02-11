multi_send_string(char *string)
{
	if (cannot_send_data()) {
		return;
	}

	multi_sexp_ensure_space_remains(strlen(string)+4);

	int start_size = packet_size;

	type[packet_size] = TYPE_STRING;

	ADD_STRING(string);
	current_argument_count += packet_size - start_size;
}
