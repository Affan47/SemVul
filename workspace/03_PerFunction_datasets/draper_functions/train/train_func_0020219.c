main(argc,argv)
int argc;
char *argv[];
{
	int i;
	extern char *optarg;
	extern int optind;
	int c;
	char *output_file = "a56.out";
	char *input_file;
	char *usage = "usage: a56  [-b]  [-l]  [-d]  [-o output-file]  input-file\n";

	while((c = getopt(argc, argv, "bldo:")) != EOF) switch (c) {
		case 'b':
			binary_listing++;
			break;
		case 'l':
			list_includes++;
			break;
		case 'd':
			ldebug++;
			break;
		case 'o':
			output_file = optarg;
			break;
		case '?':
		default:
			fatal(usage);
	}
	input_file = argv[optind++];
	if(input_file == NULL) fatal(usage);
	obj = open_write(output_file);

	pc = 0;
	seg = 0;
	pass = 1;
	reset_psects();
	include(input_file);

	pc = 0;
	seg = 0;
	pass = 2;
	reset_psects();
	include(input_file);

	psect_summary();
	dump_symtab();
	fclose(obj);
	printf("errors=%d\n", error);
	printf("warnings=%d\n", warning);
	return error ? 1 : 0;
}
