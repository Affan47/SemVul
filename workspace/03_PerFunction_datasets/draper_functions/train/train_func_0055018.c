_elf_first_scn(Elf *elf) {
    Elf_Scn *scn;

    elf_assert(elf);
    elf_assert(elf->e_magic == ELF_MAGIC);
    if ((scn = elf->e_scn_1)) {
	return scn;
    }
    if ((scn = _makescn(elf, 0))) {
	elf->e_scn_1 = elf->e_scn_n = scn;
	if (_elf_update_shnum(elf, 1)) {
	    free(scn);
	    elf->e_scn_1 = elf->e_scn_n = scn = NULL;
	}
    }
    return scn;
}
