for_each_hash(const struct hash_table *table, int (*fn)(void *))
{
	int sum = 0;
	unsigned int i;
	unsigned int size = table->size;
	struct hash_table_entry *array = table->array;

	for (i = 0; i < size; i++) {
		void *ptr = array->ptr;
		array++;
		if (ptr) {
			int val = fn(ptr);
			if (val < 0)
				return val;
			sum += val;
		}
	}
	return sum;
}
