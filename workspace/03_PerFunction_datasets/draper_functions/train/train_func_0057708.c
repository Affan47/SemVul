kasan_module_alloc(void *addr, size_t size)
{
	void *ret;
	size_t shadow_size;
	unsigned long shadow_start;

	shadow_start = (unsigned long)kasan_mem_to_shadow(addr);
	shadow_size = round_up(size >> KASAN_SHADOW_SCALE_SHIFT,
			PAGE_SIZE);

	if (WARN_ON(!PAGE_ALIGNED(shadow_start)))
		return -EINVAL;

	ret = __vmalloc_node_range(shadow_size, 1, shadow_start,
			shadow_start + shadow_size,
			GFP_KERNEL | __GFP_HIGHMEM | __GFP_ZERO,
			PAGE_KERNEL, VM_NO_GUARD, NUMA_NO_NODE,
			__builtin_return_address(0));

	if (ret) {
		find_vm_area(addr)->flags |= VM_KASAN;
		kmemleak_ignore(ret);
		return 0;
	}

	return -ENOMEM;
}
