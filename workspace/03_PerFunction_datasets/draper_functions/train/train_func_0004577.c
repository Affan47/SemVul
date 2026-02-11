chap_send_failure(struct chap_auth_data *ad, char *mschap_error, char *reply_msg)
{
	struct chap_hdr *hdr = _malloc(sizeof(*hdr) + strlen(mschap_error) + strlen(reply_msg) + 4);
	hdr->proto = htons(PPP_CHAP);
	hdr->code = CHAP_FAILURE;
	hdr->id = ad->id;
	hdr->len = htons(HDR_LEN + strlen(mschap_error) + strlen(reply_msg) + 3);

	sprintf((char *)(hdr + 1), "%s M=%s", mschap_error, reply_msg);

	if (conf_ppp_verbose)
		log_ppp_info2("send [MSCHAP-v2 Failure id=%x \"%s\"]\n", hdr->id, (char *)(hdr + 1));

	ppp_chan_send(ad->ppp, hdr, ntohs(hdr->len) + 2);

	_free(hdr);
}
