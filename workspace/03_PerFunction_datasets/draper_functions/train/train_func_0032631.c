_log_node_op(const char *action_str, struct node_op_parms *nop)
{
	const char *rely = nop->rely_on_udev ? " [trust_udev]" : "" ;
	const char *verify = nop->warn_if_udev_failed ? " [verify_udev]" : "";

	switch (nop->type) {
	case NODE_ADD:
		log_debug("%s: %s NODE_ADD (%" PRIu32 ",%" PRIu32 ") %u:%u 0%o%s%s",
			  nop->dev_name, action_str, nop->major, nop->minor, nop->uid, nop->gid, nop->mode,
			  rely, verify);
		break;
	case NODE_DEL:
		log_debug("%s: %s NODE_DEL%s%s", nop->dev_name, action_str, rely, verify);
		break;
	case NODE_RENAME:
		log_debug("%s: %s NODE_RENAME to %s%s%s", nop->old_name, action_str, nop->dev_name, rely, verify);
		break;
	case NODE_READ_AHEAD:
		log_debug("%s: %s NODE_READ_AHEAD %" PRIu32 " (flags=%" PRIu32 ")%s%s",
			  nop->dev_name, action_str, nop->read_ahead, nop->read_ahead_flags, rely, verify);
		break;
	default:
		;
	}
}
