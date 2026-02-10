get_entry_by_match_function(private_ike_sa_manager_t *this,
					ike_sa_id_t *ike_sa_id, entry_t **entry, u_int *segment,
					linked_list_match_t match, void *param)
{
	table_item_t *item;
	u_int row, seg;

	row = ike_sa_id_hash(ike_sa_id) & this->table_mask;
	seg = row & this->segment_mask;

	lock_single_segment(this, seg);
	item = this->ike_sa_table[row];
	while (item)
	{
		if (match(item->value, param))
		{
			*entry = item->value;
			*segment = seg;

			return SUCCESS;
		}
		item = item->next;
	}
	unlock_single_segment(this, seg);
	return NOT_FOUND;
}
