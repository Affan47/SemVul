hash_state_dump(hash_state_t *state, char **buf, cmph_uint32 *buflen)
{
	char *algobuf;
	size_t len;
	switch (state->hashfunc)
	{
		case CMPH_HASH_JENKINS:
			jenkins_state_dump((jenkins_state_t *)state, &algobuf, buflen);
			if (*buflen == UINT_MAX) return;
			break;
		default:
			assert(0);
	}
	*buf = (char *)malloc(strlen(cmph_hash_names[state->hashfunc]) + 1 + *buflen);
	memcpy(*buf, cmph_hash_names[state->hashfunc], strlen(cmph_hash_names[state->hashfunc]) + 1);
	DEBUGP("Algobuf is %u\n", *(cmph_uint32 *)algobuf);
	len = *buflen;
	memcpy(*buf + strlen(cmph_hash_names[state->hashfunc]) + 1, algobuf, len);
	*buflen  = (cmph_uint32)strlen(cmph_hash_names[state->hashfunc]) + 1 + *buflen;
	free(algobuf);
	return;
}
