ir_create_table(struct rc_map *rc_map,
			   const char *name, u64 rc_type, size_t size)
{
	rc_map->name = name;
	rc_map->rc_type = rc_type;
	rc_map->alloc = roundup_pow_of_two(size * sizeof(struct rc_map_table));
	rc_map->size = rc_map->alloc / sizeof(struct rc_map_table);
	rc_map->scan = kmalloc(rc_map->alloc, GFP_KERNEL);
	if (!rc_map->scan)
		return -ENOMEM;

	IR_dprintk(1, "Allocated space for %u keycode entries (%u bytes)\n",
		   rc_map->size, rc_map->alloc);
	return 0;
}
