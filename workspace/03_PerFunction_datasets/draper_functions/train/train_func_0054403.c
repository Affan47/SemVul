set_create(int bucket_count)
{
	struct set *s;

	s = (struct set *) malloc(sizeof(struct set));
	if(!s)
		return 0;

	if(bucket_count == 0)
		bucket_count = DEFAULT_SIZE;

	s->bucket_count = bucket_count;
	s->buckets = (struct entry **) calloc(bucket_count, sizeof(struct entry *));
	if(!s->buckets) {
		free(s);
		return 0;
	}

	s->size = 0;

	return s;
}
