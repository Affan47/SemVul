nlist(const char *filename, struct nlist *nl) {
    int result = -1;
    unsigned oldver;
    Elf *elf;
    int fd;

    if ((oldver = elf_version(EV_CURRENT)) != EV_NONE) {
	if ((fd = open(filename, FILE_OPEN_MODE)) != -1) {
	    if ((elf = elf_begin(fd, ELF_C_READ, NULL))) {
		result = _elf_nlist(elf, nl);
		elf_end(elf);
	    }
	    close(fd);
	}
	elf_version(oldver);
    }
    if (result) {
	while (nl->n_name && *nl->n_name) {
	    nl->n_value = 0;
	    nl++;
	}
    }
    return result;
}
