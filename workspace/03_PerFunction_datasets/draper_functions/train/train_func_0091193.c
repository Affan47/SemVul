ReplyGetPrompt(int messagetype, unsigned char *buffer, int length, gn_data *data, struct gn_statemachine *state)
{
	switch (buffer[0]) {
	case GN_AT_PROMPT: return GN_ERR_NONE;
	case GN_AT_OK: return GN_ERR_INTERNALERROR;
	default: return at_error_get(buffer, state);
	}
}
