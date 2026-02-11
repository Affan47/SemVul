replicate_stat(stat_item_t * op_it, int op_mask) {
	int retval;
	char * name;
	struct stat st_buf;

	name = namemap_get_name(op_it->o.name);
	if ( name == NULL ) {
		return;
	} else {
		if (name != op_it->o.name) {
			strcpy(op_it->o.name, name);
		}
	}

	if (op_mask & ACT_REPLICATE) {
		retval = stat(op_it->o.name, &st_buf);

		if (retval == -1 && retval != op_it->o.retval) {
			ERRORPRINTF("Stat on file with %s failed (which was not expected): %s\n", op_it->o.name, strerror(errno));
		} else if (retval != op_it->o.retval) {
			ERRORPRINTF("Stat result of file %s other than expected: %d\n", op_it->o.name, retval);
		}
	} else if (op_mask & ACT_SIMULATE) {
		simulate_stat(&op_it->o);
	}
}
