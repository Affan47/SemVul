create_mount_hash(void)
{
	FILE *f = fopen("/proc/mounts", "r");
	char buf[4096] = { };
	char *p, *p2;
	struct gr_learn_file_tmp_node *node;

	mount_hash = create_hash_table(GR_HASH_FILENAME);

	if (f == NULL)
		return;

	while(fgets(buf, sizeof(buf)-1, f)) {
		p = strchr(buf, ' ');
		if (!p)
			continue;
		p2 = strchr(p+1, ' ');
		if (!p2)
			continue;
		*p2 = '\0';
		node = conv_filename_to_struct((const char *)p+1, 0);
		insert_hash_entry(mount_hash, node);
	}

	fclose(f);
}
