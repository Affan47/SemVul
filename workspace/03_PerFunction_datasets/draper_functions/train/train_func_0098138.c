get_func_end(void *func)
{
	int r;
	Dl_info dl_info;
	ElfW(Sym) *elf_info;

	r = dladdr1(func, &dl_info, (void **) &elf_info, RTLD_DL_SYMENT);
	if (r == 0)
		return NULL;
	if (elf_info == NULL)
		return NULL;
	if (dl_info.dli_saddr == NULL)
		return NULL;

	return ((unsigned char *) func) + elf_info->st_size;
}
