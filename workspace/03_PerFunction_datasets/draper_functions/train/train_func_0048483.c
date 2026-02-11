main()
{
	int c;
	int del_blanks;

	del_blanks = 0;

	while ((c = getchar()) != EOF) {
		if (!del_blanks) {

			if (c == ' ') del_blanks = 1;
			putchar(c);
		} else {
			if (c != ' ') {
				del_blanks = 0;
				putchar(c);
			}
		}
	}
}
