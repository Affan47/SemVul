cmd_help(void)
{
	int x;
	struct macro *macro;

	puts("\nStandard commands:");
	for (x = 0; x < NUMCMDS; x++) {
		printf("%8s", commands[x].name);
		if (x % 9 == 8)
			putchar('\n');
	}
	if (x % 9)
		puts("\n");
	else
		putchar('\n');

	if (macrohead != NULL) {
		puts("Macros:");
		for (macro = macrohead, x = 0; macro != NULL; macro = macro->next) {
			if(macro->name[0] == '$')
				continue;

			printf("%8s", macro->name);
			if (x++ % 9 == 8)
				putchar('\n');
		}
		if (x % 9)
			puts("\n");
		else
			putchar('\n');
	}
}
