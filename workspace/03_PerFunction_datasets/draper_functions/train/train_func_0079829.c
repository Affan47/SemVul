logline(struct in_addr *client, char *prefix, char *s)
{
	double now = time_now();

	char addr[INET_ADDRSTRLEN];
	if (client) {
		inet_ntop(AF_INET, client, addr, sizeof(addr));
	} else {
		addr[0] = '\0';
	}
	pthread_mutex_lock(&log_lock);
	fprintf(stderr, "%s%15s %9.3f: %s", prefix, addr, now - start_time, s);
	pthread_mutex_unlock(&log_lock);
}
