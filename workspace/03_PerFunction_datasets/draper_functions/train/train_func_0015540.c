h_remove(struct hash_table *ht, struct entry *e)
{
	unsigned h = hash_64(from_oblock(e->oblock), ht->hash_bits);
	struct entry *prev;


	e = __h_lookup(ht, h, e->oblock, &prev);
	if (e)
		__h_unlink(ht, h, e, prev);
}
