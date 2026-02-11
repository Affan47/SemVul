copy_file(const char *filename, FILE *fpout) {
    FILE *fp;
    char buf[MAX_BUF];

    fp = fopen(filename, "r");
    if (fp == NULL) {
        LOG(llevError, "copy_file failed to open \"%s\", player file(s) may be corrupt.\n", filename);
        return;
    }
    while (fgets(buf, MAX_BUF, fp) != NULL)
        fputs(buf, fpout);
    fclose(fp);
}
