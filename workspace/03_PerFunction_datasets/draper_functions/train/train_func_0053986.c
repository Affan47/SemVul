layout_and_allocate(struct load_info *info, int flags)
{

	struct module *mod;
	int err;

	mod = setup_load_info(info, flags);
	if (IS_ERR(mod))
		return mod;

	err = check_modinfo(mod, info, flags);
	if (err)
		return ERR_PTR(err);


	err = module_frob_arch_sections(info->hdr, info->sechdrs,
					info->secstrings, mod);
	if (err < 0)
		return ERR_PTR(err);


	info->sechdrs[info->index.pcpu].sh_flags &= ~(unsigned long)SHF_ALLOC;


	layout_sections(mod, info);
	layout_symtab(mod, info);


	err = move_module(mod, info);
	if (err)
		return ERR_PTR(err);


	mod = (void *)info->sechdrs[info->index.mod].sh_addr;
	kmemleak_load_module(mod, info);
	return mod;
}
