dessert_meshsend_allbutone(const dessert_msg_t* msgin,
		const dessert_meshif_t *iface) {
	dessert_msg_t* msg;
	int res;


	if (dessert_msg_check(msgin, msgin->hlen + msgin->plen)) {
		dessert_warn("will not send invalid message - aborting");
		return EINVAL;
	}


	dessert_msg_clone(&msg, msgin, 1);
	res = dessert_meshsend_fast_allbutone(msg, iface);
	dessert_msg_destroy(msg);

	return res;

}
