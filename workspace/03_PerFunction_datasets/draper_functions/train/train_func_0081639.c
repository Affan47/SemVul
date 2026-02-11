extract(file_name)
     char *file_name;
{
    FILE *fp;
    unsigned char buffer[1024];
    unsigned char f1[1024], f2[1024], f3[1024];

    if ((fp = fopen(file_name, "r")) == NULL) {
	perror(file_name);
	return;
    }

    while(fgets((char *)buffer, 1024, fp) != NULL) {
	if ((buffer[0] == '\0') || (buffer[0] == '#')) continue;
	jis2ujis(buffer);
	if (sscanf((const char *)buffer, "%s%s%s", f1, f2, f3) != 3) continue;
	if (isallkana(f2) == 0) continue;
	if (isallzenkaku(f3) == 0) continue;
	if (includekanji(f3) == 0) continue;
	printf("%s %s\n", f2, f3);
    }

    fclose(fp);
}
