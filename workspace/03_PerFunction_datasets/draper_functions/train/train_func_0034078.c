script_get_header(struct fdisk_script *dp,
						     const char *name)
{
	struct list_head *p;

	list_for_each(p, &dp->headers) {
		struct fdisk_scriptheader *fi = list_entry(p, struct fdisk_scriptheader, headers);

		if (strcasecmp(fi->name, name) == 0)
			return fi;
	}

	return NULL;
}
