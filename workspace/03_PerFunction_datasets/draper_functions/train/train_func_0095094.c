xen_pmu_init(int cpu)
{
	int err;
	struct xen_pmu_params xp;
	unsigned long pfn;
	struct xen_pmu_data *xenpmu_data;

	BUILD_BUG_ON(sizeof(struct xen_pmu_data) > PAGE_SIZE);

	if (xen_hvm_domain())
		return;

	xenpmu_data = (struct xen_pmu_data *)get_zeroed_page(GFP_KERNEL);
	if (!xenpmu_data) {
		pr_err("VPMU init: No memory\n");
		return;
	}
	pfn = virt_to_pfn(xenpmu_data);

	xp.val = pfn_to_mfn(pfn);
	xp.vcpu = cpu;
	xp.version.maj = XENPMU_VER_MAJ;
	xp.version.min = XENPMU_VER_MIN;
	err = HYPERVISOR_xenpmu_op(XENPMU_init, &xp);
	if (err)
		goto fail;

	per_cpu(xenpmu_shared, cpu).xenpmu_data = xenpmu_data;
	per_cpu(xenpmu_shared, cpu).flags = 0;

	if (cpu == 0) {
		perf_register_guest_info_callbacks(&xen_guest_cbs);
		xen_pmu_arch_init();
	}

	return;

fail:
	pr_warn_once("Could not initialize VPMU for cpu %d, error %d\n",
		cpu, err);
	free_pages((unsigned long)xenpmu_data, 0);
}
