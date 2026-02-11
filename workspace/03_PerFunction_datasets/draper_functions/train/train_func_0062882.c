put_half_open(private_ike_sa_manager_t *this, entry_t *entry)
{
	table_item_t *item;
	u_int row, segment;
	rwlock_t *lock;
	half_open_t *half_open;
	chunk_t addr;

	addr = entry->other->get_address(entry->other);
	row = chunk_hash(addr) & this->table_mask;
	segment = row & this->segment_mask;
	lock = this->half_open_segments[segment].lock;
	lock->write_lock(lock);
	item = this->half_open_table[row];
	while (item)
	{
		half_open = item->value;

		if (chunk_equals(addr, half_open->other))
		{
			half_open->count++;
			break;
		}
		item = item->next;
	}

	if (!item)
	{
		INIT(half_open,
			.other = chunk_clone(addr),
			.count = 1,
		);
		INIT(item,
			.value = half_open,
			.next = this->half_open_table[row],
		);
		this->half_open_table[row] = item;
	}
	this->half_open_segments[segment].count++;
	ref_get(&this->half_open_count);
	lock->unlock(lock);
}
