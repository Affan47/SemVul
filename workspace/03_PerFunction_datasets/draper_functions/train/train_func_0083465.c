ashmem_init(void)
{
	int ret;

	ashmem_area_cachep = kmem_cache_create("ashmem_area_cache",
					       sizeof(struct ashmem_area),
					       0, 0, NULL);
	if (unlikely(!ashmem_area_cachep)) {
		pr_err("failed to create slab cache\n");
		return -ENOMEM;
	}

	ashmem_range_cachep = kmem_cache_create("ashmem_range_cache",
						sizeof(struct ashmem_range),
						0, 0, NULL);
	if (unlikely(!ashmem_range_cachep)) {
		pr_err("failed to create slab cache\n");
		return -ENOMEM;
	}

	ret = misc_register(&ashmem_misc);
	if (unlikely(ret)) {
		pr_err("failed to register misc device!\n");
		return ret;
	}

	register_shrinker(&ashmem_shrinker);

	pr_info("initialized\n");

	return 0;
}
