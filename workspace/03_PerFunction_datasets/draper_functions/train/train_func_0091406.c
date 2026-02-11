scan_linux6(int *have_v6) {
	FILE *proc = NULL;
	char address[33];
	char name[IF_NAMESIZE+1];
	int ifindex, prefix, flag3, flag4;

	proc = fopen("/proc/net/if_inet6", "r");
	if (proc == NULL)
		return;

	if (fscanf(proc, "%32[a-f0-9] %x %x %x %x %16s\n",
		   address, &ifindex, &prefix, &flag3, &flag4, name) == 6)
		*have_v6 = 1;
	fclose(proc);
	return;
}
