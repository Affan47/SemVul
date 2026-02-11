recv_bytes (int sock, char *buf, int need)
{
    while (need > 0)
    {
	int got;

	got = recv (sock, buf, need, 0);
	if (got <= 0)
	    error (1, 0, "recv() from server %s: %s",
                   current_parsed_root->hostname,
		   got == 0 ? "EOF" : SOCK_STRERROR (SOCK_ERRNO));

	buf += got;
	need -= got;
    }
}
