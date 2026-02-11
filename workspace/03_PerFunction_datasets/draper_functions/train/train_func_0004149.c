init_connection(const char *address)
{
	struct vss_addr **ta;
	struct vss_addr *tap;
	int i, n;

	n = VSS_resolve(address, NULL, &ta);
	if (n == 0) {
		thread_log(0, 0, "Could not connect to server");
		exit(2);
	}
	for (i = 1; i < n; ++i) {
		free(ta[i]);
		ta[i] = NULL;
	}
	tap = ta[0];
	free(ta);

	return (tap);
}
