next_pat(FILE *fp, double *Lab) {
	char buf[200];

	if (fgets(buf, 200, fp) == NULL)
		return 1;

	if (sscanf(buf, "%lf, %lf, %lf", &Lab[0], &Lab[1], &Lab[2]) != 3)
		return 1;

	return 0;
}
