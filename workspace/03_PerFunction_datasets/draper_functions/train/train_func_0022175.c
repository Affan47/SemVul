replicate_socket(socket_item_t * op_it, int op_mask) {
	int retval;
	int fd = op_it->o.retval;
	hash_table_t * ht;
	int32_t pid = op_it->o.info.pid;

	if (fd == -1) {
		retval = -1;
		return;
	}

	ht = get_process_ht(fd_mappings, pid);

	if (! ht) {
		ht = replicate_missing_ht(pid, op_mask);
		if (! ht) {
			return;
		}
	}

	if ( hash_table_find(ht, &fd) == NULL ) {
		fd_item_t * fd_item = new_fd_item();
		retval = get_socket_fd();

		fd_item->fd_map->my_fd = retval;
		fd_item->old_fd = fd;
		fd_item->fd_map->time_open = op_it->o.info.start;
		fd_item->fd_map->name[MAX_STRING-1] = 0;
		fd_item->fd_map->type = S_IFSOCK;
		insert_parent_fd(fd_item, op_it->o.retval);
		hash_table_insert(ht, &fd, &fd_item->item);
		increase_fd_usage(usage_map, retval);


	} else {
		ERRORPRINTF("%d: Fd %d is already opened!\n", pid, fd);
	}
}
