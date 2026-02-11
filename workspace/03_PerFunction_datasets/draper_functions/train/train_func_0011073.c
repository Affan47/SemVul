crypto_hash_walk_first_compat(struct hash_desc *hdesc,
				  struct crypto_hash_walk *walk,
				  struct scatterlist *sg, unsigned int len)
{
	walk->total = len;

	if (!walk->total) {
		walk->entrylen = 0;
		return 0;
	}

	walk->alignmask = crypto_hash_alignmask(hdesc->tfm);
	walk->sg = sg;
	walk->flags = hdesc->flags & CRYPTO_TFM_REQ_MASK;

	return hash_walk_new_entry(walk);
}
