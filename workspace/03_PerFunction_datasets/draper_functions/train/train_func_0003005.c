k_pres_res_id_by_uuid
(struct pres_file_t* pf, uint64_t uuid)
{
	uint64_t i = 0, e = pf->cur_resentries;
	struct pres_resource_table_entry_t* table = pf->rtbl->table;

	for (i = 0; i < e; ++i) {

		if (!table[i].id)
			continue;
		if (table[i].uuid == uuid)
			return table[i].id;
	}
	return 0;
}
