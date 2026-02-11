check_elf_wordsize(void *ehdr)
{
	char *e_ident = (char *) ehdr;

	if (strncmp(e_ident, ELFMAG, SELFMAG)) {
		ERROR("Not a valid ELF executable\n");
		exit(EXIT_FAILURE);
	}

	switch (e_ident[EI_CLASS]) {
		case ELFCLASS32:
		case ELFCLASS64:
			return e_ident[EI_CLASS];
		default:
			ERROR("Can not determine word size\n");
			exit(EXIT_FAILURE);
	}
}
