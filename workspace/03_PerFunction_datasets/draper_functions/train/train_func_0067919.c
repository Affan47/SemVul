dessert_msg_clone(dessert_msg_t **msgnew, const dessert_msg_t *msgold,
		uint8_t sparse) {
	dessert_msg_t *msg;
	size_t msglen = ntohs(msgold->hlen) + ntohs(msgold->plen);

	if (sparse) {
		msg = malloc(msglen);
	} else {
		msg = malloc(DESSERT_MAXFRAMEBUFLEN);
	}

	if (msg == NULL) {
		return (-errno);
	}

	memcpy(msg, msgold, msglen);

	if (sparse) {
		msg->flags |= DESSERT_FLAG_SPARSE;
	} else {
		msg->flags &= DESSERT_FLAG_SPARSE ^ DESSERT_FLAG_SPARSE;
	}

	*msgnew = msg;
	return (DESSERT_OK);

}
