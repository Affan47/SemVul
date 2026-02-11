kmemleak_alloc_percpu(const void __percpu *ptr, size_t size,
				 gfp_t gfp)
{
	unsigned int cpu;

	pr_debug("%s(0x%p, %zu)\n", __func__, ptr, size);


	if (kmemleak_enabled && ptr && !IS_ERR(ptr))
		for_each_possible_cpu(cpu)
			create_object((unsigned long)per_cpu_ptr(ptr, cpu),
				      size, 0, gfp);
	else if (kmemleak_early_log)
		log_early(KMEMLEAK_ALLOC_PERCPU, ptr, size, 0);
}
