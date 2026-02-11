_verify_rtbl_entries(struct pres_file_t* pf)
{
	uint8_t digest_chk[PRES_MAX_DIGEST_LENGTH];
	size_t digest_bytes = (pf->hdr.hashsize + 7) / 8;


	for (uint64_t i = 0; i < pf->rtbl->entries; ++i) {
		struct pres_resource_table_entry_t* e = &pf->rtbl->table[i];

		if (!e->id)
			continue;

		k_hash_reset(pf->hash);
		k_hash_update(pf->hash, e, sz_rtblentry_digest);
		k_hash_final(pf->hash, digest_chk);
		if (memcmp(e->digest, digest_chk, digest_bytes))
			goto invalid;

		uint64_t data_end = 0;
		if (_addu64(&data_end,
		e->data_offset + pf->dhdr.data_pool_start,
		e->data_size))
			goto invalid;
		if (data_end > pf->hdr.filesize)
			goto invalid;
	}

	return 0;
invalid:
	return -1;
}
