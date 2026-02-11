g2_qht_match_leafs(uint32_t hashes[], size_t num, void *data)
{
	struct qht_data *qd;
	struct qhtable *master_qht;
	size_t i, j, entries;

	master_qht = g2_qht_global_get_hzp();
	if(!master_qht)
		return;


	if(master_qht->flags.reset_needed)
		goto out;

	entries = master_qht->entries;
	do {
		mb();
		hzp_ref(HZP_QHTDAT, qd = container_of(master_qht->data, struct qht_data, data));
	} while(qd != container_of(master_qht->data, struct qht_data, data));

	if(!master_qht->data || COMP_RLE == master_qht->compressed)
		goto out_unref;


	for(i = 0, j = 0; i < num; i++)
	{
		uint32_t n = hashes[i];
		if(n > entries)
			break;
		if(!(qd->data[n / BITS_PER_CHAR] & (1 << (n % BITS_PER_CHAR))))
			hashes[j++] = n;
	}
	num = j;

	hzp_unref(HZP_QHTDAT);
	hzp_unref(HZP_QHT);

	if(num) {
		struct qht_search_walk qsw = {.hashes = hashes, .num = num, .data = data};
		g2_qht_global_search(&qsw);
	}
	return;

out_unref:
	hzp_unref(HZP_QHTDAT);
out:
	hzp_unref(HZP_QHT);
}
