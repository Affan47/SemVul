process_next_token(const char **buffer_out, char **storage,
	const char *token_end, const char *right_boundary)
{
	int error = process_trimming(*buffer_out, storage, token_end, 0);
	if (error < 0)
		return error;

	*buffer_out = token_end + 1;

	if (*buffer_out > right_boundary)
		return signature_error("signature is too short");

	return 0;
}
