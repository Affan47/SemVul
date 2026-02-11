initiator_send_HASH(struct message *msg)
{
	struct exchange *exchange = msg->exchange;
	struct ipsec_exch *ie = exchange->data;
	struct sa      *isakmp_sa = msg->isakmp_sa;
	struct ipsec_sa *isa = isakmp_sa->data;
	struct prf     *prf;
	u_int8_t       *buf;
	struct hash    *hash = hash_get(isa->hash);
	size_t          hashsize = hash->hashsize;


	buf = malloc(ISAKMP_HASH_SZ + hashsize);
	if (!buf) {
		log_error("initiator_send_HASH: malloc (%lu) failed",
			  ISAKMP_HASH_SZ + (unsigned long)hashsize);
		return -1;
	}
	if (message_add_payload(msg, ISAKMP_PAYLOAD_HASH, buf,
	    ISAKMP_HASH_SZ + hashsize, 1)) {
		free(buf);
		return -1;
	}

	LOG_DBG_BUF((LOG_NEGOTIATION, 90, "initiator_send_HASH: SKEYID_a",
		     isa->skeyid_a, isa->skeyid_len));
	prf = prf_alloc(isa->prf_type, isa->hash, isa->skeyid_a,
	    isa->skeyid_len);
	if (!prf)
		return -1;
	prf->Init(prf->prfctx);
	prf->Update(prf->prfctx, (unsigned char *)"\0", 1);
	LOG_DBG_BUF((LOG_NEGOTIATION, 90, "initiator_send_HASH: message_id",
	    exchange->message_id, ISAKMP_HDR_MESSAGE_ID_LEN));
	prf->Update(prf->prfctx, exchange->message_id,
	    ISAKMP_HDR_MESSAGE_ID_LEN);
	LOG_DBG_BUF((LOG_NEGOTIATION, 90, "initiator_send_HASH: NONCE_I_b",
	    exchange->nonce_i, exchange->nonce_i_len));
	prf->Update(prf->prfctx, exchange->nonce_i, exchange->nonce_i_len);
	LOG_DBG_BUF((LOG_NEGOTIATION, 90, "initiator_send_HASH: NONCE_R_b",
	    exchange->nonce_r, exchange->nonce_r_len));
	prf->Update(prf->prfctx, exchange->nonce_r, exchange->nonce_r_len);
	prf->Final(buf + ISAKMP_GEN_SZ, prf->prfctx);
	prf_free(prf);
	LOG_DBG_BUF((LOG_NEGOTIATION, 90, "initiator_send_HASH: HASH(3)",
	    buf + ISAKMP_GEN_SZ, hashsize));

	if (ie->group)
		message_register_post_send(msg, gen_g_xy);

	message_register_post_send(msg, post_quick_mode);

	return 0;
}
