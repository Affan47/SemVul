main(int argc, char *argv[] ) {
	FILE *file;
	int r;
	int c;
	int row = 0, col = 0;

	if (argc != 4) {
		fputs("usage: [rows] [columns] [file name]\n", stderr);
		exit(EXIT_FAILURE);
	}
	r = (int) strtol(argv[1], NULL, 10);
	c = (int) strtol(argv[2], NULL, 10);

	file = fopen(argv[3], "w");
	if (file == NULL) {
		fputs(INITIAL, stderr);
		fputs(" could not be opened.\n", stderr);
		exit(EXIT_FAILURE);
	}

	srand(time(0));


	for (row=0; row<r; row++) {
		for (col=0; col<c; col++) {
			if (rand()%2 == 0)
				fputc(DEAD, file);
			else
				fputc(LIVE, file);
		}

	}

	fclose(file);

	return EXIT_SUCCESS;
}
