fd_array_map_free(struct bpf_map *map)
{
	struct bpf_array *array = container_of(map, struct bpf_array, map);
	int i;

	synchronize_rcu();


	for (i = 0; i < array->map.max_entries; i++)
		BUG_ON(array->ptrs[i] != NULL);
	kvfree(array);
}
