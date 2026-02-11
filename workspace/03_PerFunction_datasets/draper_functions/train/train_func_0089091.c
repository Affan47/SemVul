cfg_add_hash(struct message *msg)
{
	struct ipsec_sa *isa = msg->isakmp_sa->data;
	struct hash    *hash = hash_get(isa->hash);
	u_int8_t       *hashp;

	hashp = malloc(ISAKMP_HASH_SZ + hash->hashsize);
	if (!hashp) {
		log_error("cfg_add_hash: malloc (%lu) failed",
		    ISAKMP_HASH_SZ + (unsigned long)hash->hashsize);
		return 0;
	}
	if (message_add_payload(msg, ISAKMP_PAYLOAD_HASH, hashp,
	    ISAKMP_HASH_SZ + hash->hashsize, 1)) {
		free(hashp);
		return 0;
	}
	return hashp;
}
