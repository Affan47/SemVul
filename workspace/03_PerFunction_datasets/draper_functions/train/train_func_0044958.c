kexec_apply_relocations(struct kimage *image)
{
	int i, ret;
	struct purgatory_info *pi = &image->purgatory_info;
	Elf_Shdr *sechdrs = pi->sechdrs;


	for (i = 0; i < pi->ehdr->e_shnum; i++) {
		Elf_Shdr *section, *symtab;

		if (sechdrs[i].sh_type != SHT_RELA &&
		    sechdrs[i].sh_type != SHT_REL)
			continue;


		if (sechdrs[i].sh_info >= pi->ehdr->e_shnum ||
		    sechdrs[i].sh_link >= pi->ehdr->e_shnum)
			return -ENOEXEC;

		section = &sechdrs[sechdrs[i].sh_info];
		symtab = &sechdrs[sechdrs[i].sh_link];

		if (!(section->sh_flags & SHF_ALLOC))
			continue;


		if (symtab->sh_link >= pi->ehdr->e_shnum)

			continue;


		if (sechdrs[i].sh_type == SHT_RELA)
			ret = arch_kexec_apply_relocations_add(pi->ehdr,
							       sechdrs, i);
		else if (sechdrs[i].sh_type == SHT_REL)
			ret = arch_kexec_apply_relocations(pi->ehdr,
							   sechdrs, i);
		if (ret)
			return ret;
	}

	return 0;
}
