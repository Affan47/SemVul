del_from_hostname_hash(const char *hostname, struct Client *client_p)
{
	unsigned int hashv;

	if(hostname == NULL || client_p == NULL)
		return;

	hashv = hash_hostname(hostname);

	rb_dlinkFindDestroy(client_p, &hostTable[hashv]);
}
