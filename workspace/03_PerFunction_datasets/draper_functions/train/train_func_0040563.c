k_pres_delete_id
(struct pres_file_t* pf, uint64_t id)
{
	struct pres_resource_table_entry_t e;
	struct pres_resource_table_entry_t* table = pf->rtbl->table;


	if (!pf->is_writable)
		return;

	memcpy(&e, &table[id-1], sz_res_tbl_entry);
	memset(&table[id-1], 0, sz_res_tbl_entry);

	if (_commit_meta_data(pf)) {
		memcpy(&table[id-1], &e, sz_res_tbl_entry);
		return;
	}
}
