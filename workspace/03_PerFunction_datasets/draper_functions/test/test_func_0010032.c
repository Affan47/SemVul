load_ucode_amd_ap(void)
{
	unsigned int cpu = smp_processor_id();
	struct equiv_cpu_entry *eq;
	struct microcode_amd *mc;
	u32 rev, eax;
	u16 eq_id;


	if (!cpu)
		return;

	if (!container)
		return;


	if (check_current_patch_level(&rev, false))
		return;

	eax = cpuid_eax(0x00000001);
	eq  = (struct equiv_cpu_entry *)(container + CONTAINER_HDR_SZ);

	eq_id = find_equiv_id(eq, eax);
	if (!eq_id)
		return;

	if (eq_id == this_equiv_id) {
		mc = (struct microcode_amd *)amd_ucode_patch;

		if (mc && rev < mc->hdr.patch_id) {
			if (!__apply_microcode_amd(mc))
				ucode_new_rev = mc->hdr.patch_id;
		}

	} else {
		if (!ucode_cpio.data)
			return;


		apply_ucode_in_initrd(ucode_cpio.data, ucode_cpio.size, false);
	}
}
