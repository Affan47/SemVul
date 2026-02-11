read_data(FILE * fp)
{
    if (!fp) {
        fprintf(stderr, "getdap: Whoa!!! Null stream pointer.\n");
        return false;
    }


    char c;
    while (fp && !feof(fp) && fread(&c, 1, 1, fp))
        printf("%c", c);

    return true;
}
