bpf_map_update_elem(u64 r1, u64 r2, u64 r3, u64 r4, u64 r5)
{
	struct bpf_map *map = (struct bpf_map *) (unsigned long) r1;
	void *key = (void *) (unsigned long) r2;
	void *value = (void *) (unsigned long) r3;

	WARN_ON_ONCE(!rcu_read_lock_held());

	return map->ops->map_update_elem(map, key, value, r4);
}
