read_stream(void)
{
    char *filename;
    char buf[512];
    size_t nread, nwritten;
    FILE *fp;

    filename = cli_gentemp(NULL);
    if (!(filename)) {
        return NULL;
    }

    fp = fopen(filename, "w");
    if (!(fp)) {
        free(filename);
        return NULL;
    }

    while (!feof(stdin)) {
        nwritten = 0;
        nread = fread(buf, 1, sizeof(buf), stdin);
        if (nread == 0) {
            fclose(fp);
            remove(filename);
            free(filename);
            return NULL;
        }

        while (nwritten < nread) {
            size_t i;
            i = fwrite(buf, 1, nread, fp);
            if (i == 0) {
                fclose(fp);
                remove(filename);
                free(filename);
                return NULL;
            }

            nwritten += i;
        }
    }

    fclose(fp);

    return filename;
}
