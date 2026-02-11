accountable_bio(struct cache *cache, struct bio *bio)
{
	return ((bio->bi_bdev == cache->origin_dev->bdev) &&
		!(bio->bi_rw & REQ_DISCARD));
}
