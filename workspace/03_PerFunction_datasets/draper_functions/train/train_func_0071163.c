main(int argc, char **argv)
{
	int a;
	FILE *f;
	char buf[16];

	printf("FILENAME                                 KC-NAME       "
	       "ADDR START LENGTH\n");
	for (a = 1;a < argc;a++) {
		f = fopen(argv[a], "rb");
		if (!f)
			continue;
		if (fread(buf, 1, 16, f) != 16) {
			fclose(f);
			exit(2);
		}
		if (strncmp((const char *)&buf[1], "KC-TAPE by AF", 13) != 0) {
			fclose(f);
			exit(3);
		}
		list_file(f, argv[a]);
		fclose(f);
	}

	return 0;
}
