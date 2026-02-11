_stack_node_op(node_op_t type, const char *dev_name, uint32_t major,
			  uint32_t minor, uid_t uid, gid_t gid, mode_t mode,
			  const char *old_name, uint32_t read_ahead,
			  uint32_t read_ahead_flags, int warn_if_udev_failed,
			  unsigned rely_on_udev)
{
	struct node_op_parms *nop;
	struct dm_list *noph, *nopht;
	size_t len = strlen(dev_name) + strlen(old_name) + 2;
	char *pos;


	if ((type == NODE_DEL) && _other_node_ops(type))


		dm_list_iterate_safe(noph, nopht, &_node_ops) {
			nop = dm_list_item(noph, struct node_op_parms);
			if (!strcmp(dev_name, nop->dev_name)) {
				_log_node_op("Unstacking", nop);
				_del_node_op(nop);
				if (!_other_node_ops(type))
					break;
			}
		}
	else if ((type == NODE_ADD) && _count_node_ops[NODE_DEL])


		dm_list_iterate_safe(noph, nopht, &_node_ops) {
			nop = dm_list_item(noph, struct node_op_parms);
			if ((nop->type == NODE_DEL) &&
			    !strcmp(dev_name, nop->dev_name)) {
				_log_node_op("Unstacking", nop);
				_del_node_op(nop);
				break;
			}
		}
	else if (type == NODE_RENAME)


		dm_list_iterate_safe(noph, nopht, &_node_ops) {
			nop = dm_list_item(noph, struct node_op_parms);
			if (!strcmp(old_name, nop->dev_name)) {
				_log_node_op("Unstacking", nop);
				_del_node_op(nop);
			}
		}
	else if (type == NODE_READ_AHEAD) {

		rely_on_udev = 0;
		warn_if_udev_failed = 0;
	}

	if (!(nop = dm_malloc(sizeof(*nop) + len))) {
		log_error("Insufficient memory to stack mknod operation");
		return 0;
	}

	pos = nop->names;
	nop->type = type;
	nop->major = major;
	nop->minor = minor;
	nop->uid = uid;
	nop->gid = gid;
	nop->mode = mode;
	nop->read_ahead = read_ahead;
	nop->read_ahead_flags = read_ahead_flags;
	nop->rely_on_udev = rely_on_udev;


	nop->warn_if_udev_failed = rely_on_udev ? 0 : warn_if_udev_failed;

	_store_str(&pos, &nop->dev_name, dev_name);
	_store_str(&pos, &nop->old_name, old_name);

	_count_node_ops[type]++;
	dm_list_add(&_node_ops, &nop->list);

	_log_node_op("Stacking", nop);

	return 1;
}
