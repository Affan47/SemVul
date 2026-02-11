readHeaderString(FILE * fp, char *valueString, double *value)
{
    static char format[100];


    G_snprintf(format, 100, "%s %%lf", valueString);
    if (fscanf(fp, format, value) != 1) {
	G_debug(3, "bad value for [%s]", valueString);
	fatalError("readHeaderString: header value invalid");
    }
    while (fgetc(fp) != '\n') ;
}
