userparse(const char *buffer, VALUE_PAIR **first_pair)
{
	VALUE_PAIR	*vp;
	const char	*p;
	FR_TOKEN	last_token = T_OP_INVALID;
	FR_TOKEN	previous_token;


	if (buffer[0] == 0)
		return T_EOL;

	p = buffer;
	do {
		previous_token = last_token;
		if ((vp = pairread(&p, &last_token)) == NULL) {
			return last_token;
		}
		pairadd(first_pair, vp);
	} while (*p && (last_token == T_COMMA));


	if (last_token == T_HASH) {
		return previous_token;
	}


	return last_token;
}
