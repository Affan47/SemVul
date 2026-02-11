vi_openAtEnd(char *filename, long *len)
{
	FILE *fp = NULL;

	if ((fp = fopen(filename, "rb")) == NULL) goto err;
	if ((fseek(fp, 0, SEEK_END)) == -1) goto err;
	if ((*len = ftell(fp)) == -1) goto err;
	return fp;
err:
	if (fp != NULL) fclose(fp);
	return NULL;
}
