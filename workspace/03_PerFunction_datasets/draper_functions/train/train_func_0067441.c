ima_eventdigest_ng_init(struct ima_event_data *event_data,
			    struct ima_field_data *field_data)
{
	u8 *cur_digest = NULL, hash_algo = HASH_ALGO_SHA1;
	u32 cur_digestsize = 0;

	if (event_data->violation)
		goto out;

	cur_digest = event_data->iint->ima_hash->digest;
	cur_digestsize = event_data->iint->ima_hash->length;

	hash_algo = event_data->iint->ima_hash->algo;
out:
	return ima_eventdigest_init_common(cur_digest, cur_digestsize,
					   hash_algo, field_data);
}
