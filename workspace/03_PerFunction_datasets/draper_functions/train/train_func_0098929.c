load_microcode_amd(int cpu, u8 family, const u8 *data, size_t size)
{
	enum ucode_state ret;


	free_equiv_cpu_table();

	ret = __load_microcode_amd(family, data, size);

	if (ret != UCODE_OK)
		cleanup();

#ifdef CONFIG_X86_32

	if (cpu_data(cpu).cpu_index == boot_cpu_data.cpu_index) {
		struct ucode_patch *p = find_patch(cpu);
		if (p) {
			memset(amd_ucode_patch, 0, PATCH_MAX_SIZE);
			memcpy(amd_ucode_patch, p->data, min_t(u32, ksize(p->data),
							       PATCH_MAX_SIZE));
		}
	}
#endif
	return ret;
}
