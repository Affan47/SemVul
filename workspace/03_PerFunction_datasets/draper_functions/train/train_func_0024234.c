hash_state_pack(hash_state_t *state, void *hash_packed)
{
	switch (state->hashfunc)
	{
		case CMPH_HASH_JENKINS:

			jenkins_state_pack((jenkins_state_t *)state, hash_packed);
			break;
		default:
			assert(0);
	}
	return;
}
