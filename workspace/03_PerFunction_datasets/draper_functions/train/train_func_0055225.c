qla4xxx_check_existing_isid(struct list_head *list_nt, uint8_t *isid)
{
	struct qla_ddb_index *nt_ddb_idx, *nt_ddb_idx_tmp;
	struct dev_db_entry *fw_ddb_entry;

	list_for_each_entry_safe(nt_ddb_idx, nt_ddb_idx_tmp, list_nt, list) {
		fw_ddb_entry = &nt_ddb_idx->fw_ddb;

		if (memcmp(&fw_ddb_entry->isid[0], &isid[0],
			   sizeof(nt_ddb_idx->fw_ddb.isid)) == 0) {
			return QLA_SUCCESS;
		}
	}
	return QLA_ERROR;
}
