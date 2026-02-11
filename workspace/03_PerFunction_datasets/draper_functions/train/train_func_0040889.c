adjoin(struct dm_table *table, struct dm_target *ti)
{
	struct dm_target *prev;

	if (!table->num_targets)
		return !ti->begin;

	prev = &table->targets[table->num_targets - 1];
	return (ti->begin == (prev->begin + prev->len));
}
