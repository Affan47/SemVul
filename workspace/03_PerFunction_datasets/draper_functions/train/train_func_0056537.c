_cred_state_unpack_one(Buf buffer)
{
	cred_state_t *s = xmalloc(sizeof(*s));

	safe_unpack32(&s->jobid, buffer);
	safe_unpack32(&s->stepid, buffer);
	safe_unpack_time(&s->ctime, buffer);
	safe_unpack_time(&s->expiration, buffer);
	return s;

unpack_error:
	_cred_state_destroy(s);
	return NULL;
}
