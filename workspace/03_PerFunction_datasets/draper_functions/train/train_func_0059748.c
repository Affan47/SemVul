elf_flagelf(Elf *elf, Elf_Cmd cmd, unsigned flags) {
    if (!elf) {
	return 0;
    }
    elf_assert(elf->e_magic == ELF_MAGIC);
    return _elf_flag(&elf->e_elf_flags, cmd, flags);
}
