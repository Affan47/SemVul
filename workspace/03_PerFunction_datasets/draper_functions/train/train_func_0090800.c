argvToString(char *argv[], int argc, char line[200])
{
	int i = 0;

	strcpy(line, "^");
	while (argc > 0) {
		strcat(line, argv[i]);
		strcat(line, "^");
		argc--;
		i++;
	}
	strcat(line, "\n");
}
