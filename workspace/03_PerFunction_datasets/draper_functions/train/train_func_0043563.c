ask_reclass(void)
{
    char *line, str[5];
    FILE *fp;
    register int i, j;

    G_sleep_on_error(0);


    G_system("clear");
    fprintf(stderr,
	    "\n\n    Please input attribute groups in table form just like in a");
    fprintf(stderr,
	    "\n      GRASS reclass table; Put a space before the = sign. After");
    fprintf(stderr,
	    "\n      each line of input, the program will confirm what you typed.");
    fprintf(stderr, "\n      Maximum number of groups is 25\n");
    fprintf(stderr, "    Example: 1 4 9  101 thru 120 = 1 forest\n");
    fprintf(stderr, "             10 thru 100 = 2  prairie\n");
    fprintf(stderr, "             end\n");


  back:
    fp = fopen0("r.le.para/recl_tb", "w");


    for (j = 0; j < 25; j++) {
	line = (char *)G_calloc(512, sizeof(char));
	fprintf(stderr, "  > ");


	get_1recl(line, 0);
	fputs(line, fp);
	if (line[0] == 'e' && line[1] == 'n' && line[2] == 'd') {
	    G_free(line);
	    break;
	}
	G_free(line);
    }

    fclose(fp);
    return;
}
