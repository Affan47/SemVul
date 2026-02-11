xen_setup_shared_info(void)
{
	if (!xen_feature(XENFEAT_auto_translated_physmap)) {
		set_fixmap(FIX_PARAVIRT_BOOTMAP,
			   xen_start_info->shared_info);

		HYPERVISOR_shared_info =
			(struct shared_info *)fix_to_virt(FIX_PARAVIRT_BOOTMAP);
	} else
		HYPERVISOR_shared_info =
			(struct shared_info *)__va(xen_start_info->shared_info);

#ifndef CONFIG_SMP

	xen_setup_vcpu_info_placement();
#endif

	xen_setup_mfn_list_list();
}
