dessert_msg_check_cb(dessert_msg_t* msg, size_t len,
		dessert_msg_proc_t *proc, const dessert_meshif_t *iface,
		dessert_frameid_t id) {
	if (dessert_msg_check(msg, len)) {
		dessert_debug("invalid package - discarding");
		return DESSERT_MSG_DROP;
	}
	return DESSERT_MSG_KEEP;
}
