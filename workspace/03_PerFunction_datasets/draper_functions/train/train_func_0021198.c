has_constraint(struct isl_ctx *ctx, struct isl_hash_table *table,
	isl_int *con, unsigned len, int n)
{
	struct isl_hash_table_entry *entry;
	struct max_constraint *c;
	uint32_t c_hash;

	c_hash = isl_seq_get_hash(con + 1, len);
	entry = isl_hash_table_find(ctx, table, c_hash, max_constraint_equal,
			con + 1, 0);
	if (!entry)
		return 0;
	c = entry->data;
	if (c->count < n)
		return 0;
	return isl_int_eq(c->c->row[0][0], con[0]);
}
