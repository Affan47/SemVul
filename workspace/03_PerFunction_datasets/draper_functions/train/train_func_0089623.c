zs_map_object(struct zs_pool *pool, unsigned long handle,
			enum zs_mapmode mm)
{
	struct page *page;
	unsigned long obj, obj_idx, off;

	unsigned int class_idx;
	enum fullness_group fg;
	struct size_class *class;
	struct mapping_area *area;
	struct page *pages[2];
	void *ret;

	BUG_ON(!handle);


	BUG_ON(in_interrupt());


	pin_tag(handle);

	obj = handle_to_obj(handle);
	obj_to_location(obj, &page, &obj_idx);
	get_zspage_mapping(get_first_page(page), &class_idx, &fg);
	class = pool->size_class[class_idx];
	off = obj_idx_to_offset(page, obj_idx, class->size);

	area = &get_cpu_var(zs_map_area);
	area->vm_mm = mm;
	if (off + class->size <= PAGE_SIZE) {

		area->vm_addr = kmap_atomic(page);
		ret = area->vm_addr + off;
		goto out;
	}


	pages[0] = page;
	pages[1] = get_next_page(page);
	BUG_ON(!pages[1]);

	ret = __zs_map_object(area, pages, off, class->size);
out:
	if (!class->huge)
		ret += ZS_HANDLE_SIZE;

	return ret;
}
