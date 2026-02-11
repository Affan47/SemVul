eat_space (ParserState *state, int res)
{


	while (*state->ptr == ' ')
		state->ptr++;
	return res;
}
