print_target(const char *prefix, const struct xt_set_info *info)
{
	int i;
	char setname[IPSET_MAXNAMELEN];

	if (info->index == IPSET_INVALID_ID)
		return;
	get_set_byid(setname, info->index);
	printf(" %s %s", prefix, setname);
	for (i = 1; i <= info->dim; i++) {
		printf("%s%s",
		       i == 1 ? " " : ",",
		       info->flags & (1 << i) ? "src" : "dst");
	}
}
