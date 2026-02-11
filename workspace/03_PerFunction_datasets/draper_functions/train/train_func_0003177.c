ro_node(struct ro_spine *s)
{
	struct dm_block *block;

	BUG_ON(!s->count);
	block = s->nodes[s->count - 1];

	return dm_block_data(block);
}
