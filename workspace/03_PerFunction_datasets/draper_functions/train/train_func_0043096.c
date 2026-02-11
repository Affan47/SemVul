hq_close(void)
{
	struct hash_table *ht;

	ht = &hash_table;

	ht->flags &= ~(HASH_QUEUE_OPEN);
	ht->flags |= HASH_QUEUE_CLOSED;

	if (!(pc->flags & HASH))
		return(0);

	if (ht->flags & HASH_QUEUE_NONE)
		return(0);

	ht->flags &= ~HASH_QUEUE_FULL;

	return(ht->index);
}
