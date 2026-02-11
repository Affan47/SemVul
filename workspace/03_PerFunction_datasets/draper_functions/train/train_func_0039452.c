as_append_char (struct snprintf_state *state, unsigned char c)
{
    if(!as_reserve (state, 1))
	*state->s++ = c;
}
