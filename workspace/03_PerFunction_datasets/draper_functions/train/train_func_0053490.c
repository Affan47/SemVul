realm_init(struct xt_entry_match *m)
{
	const char file[] = "/etc/iproute2/rt_realms";
	realms = xtables_lmap_init(file);
	if (realms == NULL && errno != ENOENT)
		fprintf(stderr, "Warning: %s: %s\n", file, strerror(errno));
}
