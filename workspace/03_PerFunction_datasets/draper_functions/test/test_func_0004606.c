nettel_cleanup(void)
{
#ifdef CONFIG_MTD_CFI_INTELEXT
	unregister_reboot_notifier(&nettel_notifier_block);
#endif
	if (amd_mtd) {
		mtd_device_unregister(amd_mtd);
		map_destroy(amd_mtd);
	}
	if (nettel_mmcrp) {
		iounmap(nettel_mmcrp);
		nettel_mmcrp = NULL;
	}
	if (nettel_amd_map.virt) {
		iounmap(nettel_amd_map.virt);
		nettel_amd_map.virt = NULL;
	}
#ifdef CONFIG_MTD_CFI_INTELEXT
	if (intel_mtd) {
		mtd_device_unregister(intel_mtd);
		map_destroy(intel_mtd);
	}
	if (nettel_intel_map.virt) {
		iounmap(nettel_intel_map.virt);
		nettel_intel_map.virt = NULL;
	}
#endif
}
