hmap_put(HMap *map, void *key, void *value)
{
    HMapEntry *entry;
    uint32_t index;

    index = hmap_hash(map, key);
    if (key == NULL) {
	for (entry = map->buckets[index]; entry != NULL; entry = entry->next) {
	    if (entry->key == NULL) {
		void *old_value = entry->value;
		entry->value = value;
		return old_value;
	    }
	}
    } else {
	for (entry = map->buckets[index]; entry != NULL; entry = entry->next) {
	    if (map->compare(key, entry->key) == 0) {
		void *old_value = entry->value;
		entry->value = value;
		return old_value;
	    }
	}
    }

    map->size++;
    if (map->size > map->threshold) {
	hmap_rehash(map);
	index = hmap_hash(map, key);
    }

    entry = xmalloc(sizeof(HMapEntry));
    entry->key = key;
    entry->value = value;
    entry->next = map->buckets[index];
    map->buckets[index] = entry;

    return NULL;
}
