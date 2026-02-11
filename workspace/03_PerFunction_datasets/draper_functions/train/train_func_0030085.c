zram_meta_alloc(char *pool_name, u64 disksize)
{
	size_t num_pages;
	struct zram_meta *meta = kmalloc(sizeof(*meta), GFP_KERNEL);

	if (!meta)
		return NULL;

	num_pages = disksize >> PAGE_SHIFT;
	meta->table = vzalloc(num_pages * sizeof(*meta->table));
	if (!meta->table) {
		pr_err("Error allocating zram address table\n");
		goto out_error;
	}

	meta->mem_pool = zs_create_pool(pool_name, GFP_NOIO | __GFP_HIGHMEM);
	if (!meta->mem_pool) {
		pr_err("Error creating memory pool\n");
		goto out_error;
	}

	return meta;

out_error:
	vfree(meta->table);
	kfree(meta);
	return NULL;
}
