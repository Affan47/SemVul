search_lookup_hash(cell table, cell klass, cell hashcode)
{
	array *buckets = untag<array>(table);
	cell bucket = array_nth(buckets,hashcode & (array_capacity(buckets) - 1));
	if(TAG(bucket) == ARRAY_TYPE)
		return search_lookup_alist(bucket,klass);
	else
		return bucket;
}
