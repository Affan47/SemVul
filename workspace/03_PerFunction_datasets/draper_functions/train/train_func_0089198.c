code_state_init(struct code_state *code_state,
			   const unsigned char *code, int code_length)
{
	code_state->code_length = code_length;
	code_state->code = malloc(code_length);
	if (!code_state->code)
		return warn("out of memory"), -ENOMEM;

	memcpy(code_state->code, code, code_length);
	return 0;
}
