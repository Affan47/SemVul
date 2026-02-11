main(int argc, char **argv)
{
	int show_absolute_syms, show_absolute_relocs;
	int as_text, use_real_mode;
	const char *fname;
	FILE *fp;
	int i;

	show_absolute_syms = 0;
	show_absolute_relocs = 0;
	as_text = 0;
	use_real_mode = 0;
	fname = NULL;
	for (i = 1; i < argc; i++) {
		char *arg = argv[i];
		if (*arg == '-') {
			if (strcmp(arg, "--abs-syms") == 0) {
				show_absolute_syms = 1;
				continue;
			}
			if (strcmp(arg, "--abs-relocs") == 0) {
				show_absolute_relocs = 1;
				continue;
			}
			if (strcmp(arg, "--text") == 0) {
				as_text = 1;
				continue;
			}
			if (strcmp(arg, "--realmode") == 0) {
				use_real_mode = 1;
				continue;
			}
		}
		else if (!fname) {
			fname = arg;
			continue;
		}
		usage();
	}
	if (!fname) {
		usage();
	}
	regex_init(use_real_mode);
	fp = fopen(fname, "r");
	if (!fp) {
		die("Cannot open %s: %s\n",
			fname, strerror(errno));
	}
	read_ehdr(fp);
	read_shdrs(fp);
	read_strtabs(fp);
	read_symtabs(fp);
	read_relocs(fp);
	if (show_absolute_syms) {
		print_absolute_symbols();
		return 0;
	}
	if (show_absolute_relocs) {
		print_absolute_relocs();
		return 0;
	}
	emit_relocs(as_text, use_real_mode);
	return 0;
}
