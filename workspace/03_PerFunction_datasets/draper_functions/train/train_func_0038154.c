dessert_msg_delext(dessert_msg_t *msg, dessert_ext_t *ext) {


	if ((((uint8_t *) ext) < ((uint8_t *) msg)) || (((uint8_t *) ext)
			> (((uint8_t *) msg) + ntohs(msg->hlen)))) {
		dessert_debug("extension not within packet header - won't remove");
		return DESSERT_ERR;
	}

	msg->hlen = htons(ntohs(msg->hlen) - ext->len);

	memmove(ext, ((uint8_t *) ext) + ext->len, (ntohs(msg->hlen)
			+ ntohs(msg->plen)) - (((uint8_t *) ext) - ((uint8_t *) msg)));

	return DESSERT_OK;
}
