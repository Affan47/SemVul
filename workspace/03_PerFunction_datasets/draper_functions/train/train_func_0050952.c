replicate_read(read_item_t * op_it, int op_mask) {
	int64_t retval = 0;
	int fd = op_it->o.fd;
	fd_item_t * fd_item;
	int myfd;
	item_t * fd_map;
	char * data;
	int32_t pid = op_it->o.info.pid;
	hash_table_t * ht;

	ht = get_process_ht(fd_mappings, pid);

	if (! ht) {
		ht = replicate_missing_ht(pid, op_mask);
		if (! ht) {
			return;
		}
	}

	if ( (fd_map = replicate_get_fd_map(ht, fd, &(op_it->o.info), op_mask)) == NULL) {
		return;
	} else {
		fd_item = hash_table_entry(fd_map, fd_item_t, item);
		myfd = fd_item->fd_map->my_fd;

		if ( ! supported_type(fd_item->fd_map->type)) {

			return;
		}

		if (op_it->o.size > MAX_DATA) {
			data = malloc(op_it->o.size);
		} else {
			data = data_buffer;
		}

		if (op_mask & ACT_SIMULATE) {
			retval = op_it->o.retval;
			if (op_it->o.retval != -1) {
				simulate_read(fd_item, op_it);
			}
		} else if ( op_mask & ACT_REPLICATE) {
			retval = read(myfd, data_buffer, op_it->o.size);
		} else {
			assert(0);
		}
		fd_item->fd_map->cur_pos += retval;


		if ( op_it->o.size > MAX_DATA) {
			free(data);
		}

		if (retval == -1 && retval != op_it->o.retval) {
			ERRORPRINTF("%d: Read from fd %d->%d failed: %s\n", pid, fd, myfd, strerror(errno));

		} else if (retval != op_it->o.size && retval != op_it->o.retval) {
			DEBUGPRINTF("Warning, %"PRIi64" bytes were successfully read \
(expected: %"PRIi64")\n", retval, op_it->o.retval);
		}
	}
}
