pmap_overrule(struct pmap *pm, const void *p, size_t size, vmf_type_t type)
{
	const void *base = p;
	size_t remain = size;

	mutex_lock(&pm->lock);

	while (size_is_positive(remain)) {
		size_t idx;
		struct vm_fragment *vmf = pmap_lookup(pm, base, &idx);
		size_t len;

		g_assert(size_is_non_negative(idx));

		if (NULL == vmf) {
			const void *end = const_ptr_add_offset(base, remain);
			size_t gap;


			if (idx >= pm->count)
				break;

			vmf = &pm->array[idx];

			if (ptr_cmp(end, vmf->start) <= 0) {
				mutex_unlock(&pm->lock);
				return;
			}


			g_assert_log(vmf_is_foreign(vmf),
				"vmf={%s}, base=%p, remain=%zu",
				vmf_to_string(vmf), base, remain);

			gap = ptr_diff(vmf->start, base);
			g_assert(size_is_positive(gap));
			g_assert(gap <= remain);

			remain -= gap;
			base = vmf->start;


		}


		vmm_stats.pmap_overruled++;
		len = ptr_diff(vmf->end, base);

		g_assert_log(size_is_positive(len), "len = %zu", len);


		g_assert_log(VMF_MAPPED == type || vmf_is_foreign(vmf),
			"vmf={%s}, base=%p, len=%zu, remain=%zu",
			vmf_to_string(vmf), base, len, remain);

		g_assert(!vmf_is_native(vmf));

		if (len < remain) {
			pmap_remove_from(pm, vmf, base, len);
			base = const_ptr_add_offset(base, len);
			remain -= len;
		} else {
			pmap_remove_from(pm, vmf, base, remain);
			break;
		}
	}

	mutex_unlock(&pm->lock);
}
