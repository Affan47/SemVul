is_binary_stripped(char *filename)
{
#ifdef GDB_5_3
        struct _bfd *bfd;
#else
        struct bfd *bfd;
#endif
	int number_of_symbols;

	if ((bfd = bfd_openr(filename, NULL)) == NULL) {
		error(INFO, "cannot open ELF file: %s\n", filename);
		return FALSE;
	}

	if (!bfd_check_format(bfd, bfd_object)) {
		error(INFO, "invalid ELF file: %s\n", filename);
		bfd_close(bfd);
		return FALSE;
	}

	number_of_symbols = bfd_canonicalize_symtab(bfd, NULL);

	bfd_close(bfd);

	return (number_of_symbols == 0);
}
