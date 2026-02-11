viafb_remove_proc(struct viafb_shared *shared)
{
	struct proc_dir_entry *viafb_entry = shared->proc_entry,
		*iga1_entry = shared->iga1_proc_entry,
		*iga2_entry = shared->iga2_proc_entry;

	if (!viafb_entry)
		return;

	remove_proc_entry("output_devices", iga2_entry);
	remove_proc_entry("iga2", viafb_entry);
	remove_proc_entry("output_devices", iga1_entry);
	remove_proc_entry("iga1", viafb_entry);
	remove_proc_entry("supported_output_devices", viafb_entry);

#ifdef CONFIG_FB_VIA_DIRECT_PROCFS
	remove_proc_entry("dvp0", viafb_entry);
	remove_proc_entry("dvp1", viafb_entry);
	remove_proc_entry("dfph", viafb_entry);
	remove_proc_entry("dfpl", viafb_entry);
	if (IS_VT1636(shared->chip_info.lvds_chip_info)
		|| IS_VT1636(shared->chip_info.lvds_chip_info2))
		remove_proc_entry("vt1636", viafb_entry);
#endif

	remove_proc_entry("viafb", NULL);
}
