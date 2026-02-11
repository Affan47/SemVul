del_func(void *rec, size_t recsize,
		    int *doupdate, void *arg)
{
	unsigned char *recp=(unsigned char *)rec;
	struct walk_info *wi=(struct walk_info *)arg;
	time_t timeout;
	size_t session_id_len;

	if (recsize < sizeof(timeout)+sizeof(session_id_len))
		return (0);

	memcpy(&timeout, recp, sizeof(timeout));

	if (timeout <= wi->now)
		return (0);

	memcpy(&session_id_len, recp + sizeof(timeout),
	       sizeof(session_id_len));

	if (session_id_len != (size_t)wi->id_len ||
	    memcmp(recp + sizeof(timeout) + sizeof(session_id_len),
		   wi->id, session_id_len))
		return (0);

	timeout=0;
	memcpy(recp, &timeout, sizeof(timeout));
	*doupdate=1;
#ifdef TLSCACHEDEBUG
	fprintf(stderr, "INFO: TLSCACHE: deleted\n");
#endif
	return (1);
}
