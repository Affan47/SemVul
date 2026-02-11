hash_lookup(struct mq_policy *mq, dm_oblock_t oblock)
{
	unsigned h = hash_64(from_oblock(oblock), mq->hash_bits);
	struct hlist_head *bucket = mq->table + h;
	struct entry *e;

	hlist_for_each_entry(e, bucket, hlist)
		if (e->oblock == oblock) {
			hlist_del(&e->hlist);
			hlist_add_head(&e->hlist, bucket);
			return e;
		}

	return NULL;
}
