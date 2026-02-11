mirror_show_table(unsigned long target)
{
	unsigned int i, nr_mir;
	unsigned long ms, rh, log, log_type, mir_size, mir_head, mir, dm_dev;
	unsigned long long offset;
	char buf[BUFSIZE];


	GET_VALUE(target, dm_target, private, ms);


	GET_ADDR(ms, mirror_set, rh, rh);
	GET_VALUE(rh, region_hash, log, log);
	GET_VALUE(log, dirty_log, type, log_type);
	GET_PTR_STR(log_type, dirty_log_type, name, buf, BUFSIZE);
	fprintf(fp, "  log:%s", buf);


	fprintf(fp, " dev:");
	mir_size = STRUCT_SIZE("struct mirror");
	GET_ADDR(ms, mirror_set, mirror, mir_head);
	GET_VALUE(ms, mirror_set, nr_mirrors, nr_mir);
	for (i = 0; i < nr_mir; i++) {
		mir = mir_head + mir_size * i;


		GET_VALUE(mir, mirror, dev, dm_dev);
		GET_STR(dm_dev, dm_dev, name, buf, BUFSIZE);


		GET_VALUE(mir, mirror, offset, offset);

		fprintf(fp, "%s(%llu)%s", buf, offset,
			i == nr_mir - 1 ? "" : ",");
	}
	if (i != nr_mir)
		fprintf(fp, " ERROR: dev are less than nr_mir:%d", nr_mir);
}
