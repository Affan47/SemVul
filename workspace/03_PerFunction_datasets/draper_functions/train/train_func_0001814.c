vmm_dump_pmap_log(logagent_t *la)
{
	struct pmap *pm = vmm_pmap();
	size_t i;
	time_t now = tm_time();

	mutex_lock(&pm->lock);

	log_debug(la, "VMM current %s pmap (%zu/%zu region%s):",
		pm == &kernel_pmap ? "kernel" :
		pm == &local_pmap ? "local" : "unknown",
		pm->count, pm->size, 1 == pm->count ? "" : "s");

	for (i = 0; i < pm->count; i++) {
		struct vm_fragment *vmf = &pm->array[i];
		size_t hole = 0;

		if (i < pm->count - 1) {
			const void *next = pm->array[i+1].start;
			hole = ptr_diff(next, vmf->end);
		}

		log_debug(la, "VMM [%p, %p] %zuKiB %s%s%s%s (%s)%s",
			vmf->start, const_ptr_add_offset(vmf->end, -1),
			vmf_size(vmf) / 1024, vmf_type_str(vmf->type),
			hole ? " + " : "",
			hole ? size_t_to_string(hole / 1024) : "",
			hole ? "KiB hole" : "",
			compact_time(delta_time(now, vmf->mtime)),
			size_is_non_negative(hole) ? "" : " *UNSORTED*");
	}

	mutex_unlock(&pm->lock);
}
