load_ucode_intel_bsp(void)
{
	u64 start, size;
#ifdef CONFIG_X86_32
	struct boot_params *p;

	p	= (struct boot_params *)__pa_nodebug(&boot_params);
	size	= p->hdr.ramdisk_size;


	start	= (size ? p->hdr.ramdisk_image : 0);

	_load_ucode_intel_bsp((struct mc_saved_data *)__pa_nodebug(&mc_saved_data),
			      (unsigned long *)__pa_nodebug(&mc_saved_in_initrd),
			      start, size);
#else
	size	= boot_params.hdr.ramdisk_size;
	start	= (size ? boot_params.hdr.ramdisk_image + PAGE_OFFSET : 0);

	_load_ucode_intel_bsp(&mc_saved_data, mc_saved_in_initrd, start, size);
#endif
}
