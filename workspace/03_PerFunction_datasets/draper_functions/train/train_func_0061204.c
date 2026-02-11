dump_str(FILE * f, char **strarr)
{
    int i;

    i = 0;
    while (strarr[i] != NULL) {
	fprintf(f, "%i: %s", i, strarr[i]);
	i++;
    }
}
