main(int argc, char **argv)
{
	int opt;
	encoder f = printf_encode;
	unsigned flags = 0;

	while ((opt = getopt(argc, argv, "?Vpeun")) != -1) {
		switch (opt) {
		case 'V':
			fputs("printable v" VERSION " <" HOME ">\n"
			      DESCRIPTION "\n"
			      "Copyright (c) 2010, Alejandro Mery <amery@geeks.cl>\n",
			      stderr);
			return 0;
		case 'p': f = printf_encode; break;
		case 'e': f = echo_encode; break;
		case 'u': f = url_encode; break;
		case 'n': flags ^= SKIP_NL; break;
		default:
			fprintf(stderr,
				"printable v" VERSION "\n" DESCRIPTION "\n\n"
				 "Usage: %s [-V] [-peu] [<strings> ...]\n\n"
				 "  -V   print version and exit\n"
				 "  -p   encode for printf()\n"
				 "  -e   encode for `echo`\n"
				 "  -u   encode for the querystring of a url\n"
				 "  -n   don't encode new lines\n"
				 "\n(stdin is used if no string is given)\n",
				 argv[0]);
			 return(1);
		}
	}

	if (optind < argc) {
		for(int i = optind; i < argc; i++) {
			print_encoded(argv[i], strlen(argv[i]), f, flags);
			stdout_all("\n",1);
		}
	} else {
		print_stdin_encoded(f, flags);
	}
	return 0;
}
