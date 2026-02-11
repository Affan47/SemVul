multi_get_string(SCP_string &buffer)
{
	char tempstring[TOKEN_LENGTH];
	int starting_offset = offset;

	if (!Multi_sexp_bytes_left || !current_argument_count) {
		return false;
	}

	GET_STRING(tempstring);
	buffer = tempstring;
	multi_reduce_counts(offset - starting_offset);

	return true;
}
