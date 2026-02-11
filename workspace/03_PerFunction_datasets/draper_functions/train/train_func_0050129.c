krb5_get_login_princ(luser, princ_list)
    const char *luser;
    char ***princ_list;
{
    struct stat sbuf;
    struct passwd *pwd;
    char pbuf[MAXPATHLEN];
    FILE *fp;
    char * linebuf;
    char *newline;
    int gobble, result;
    char ** buf_out;
    struct stat st_temp;
    int count = 0, chunk_count = 1;


    if ((pwd = getpwnam(luser)) == NULL) {
        return 0;
    }
    result = snprintf(pbuf, sizeof(pbuf), "%s/.k5login", pwd->pw_dir);
    if (SNPRINTF_OVERFLOW(result, sizeof(pbuf))) {
        fprintf(stderr, _("home directory path for %s too long\n"), luser);
        exit (1);
    }

    if (stat(pbuf, &st_temp)) {
        return 0;
    }


    if ((fp = fopen(pbuf, "r")) == NULL) {
        return 0;
    }


    if (fstat(fileno(fp), &sbuf)) {
        fclose(fp);
        return 0;
    }
    if ((sbuf.st_uid != pwd->pw_uid) && sbuf.st_uid) {
        fclose(fp);
        return 0;
    }


    if( !(linebuf = (char *) calloc (BUFSIZ, sizeof(char)))) return ENOMEM;

    if (!(buf_out = (char **) malloc( CHUNK * sizeof(char *)))) return ENOMEM;

    while ( fgets(linebuf, BUFSIZ, fp) != NULL) {

        linebuf[BUFSIZ-1] = '\0';
        newline = NULL;

        if ((newline = strchr(linebuf, '\n')))
            *newline = '\0';

        buf_out[count] = linebuf;
        count ++;

        if (count == (chunk_count * CHUNK -1)){
            chunk_count ++;
            if (!(buf_out = (char **) realloc(buf_out,
                                              chunk_count * CHUNK * sizeof(char *)))){
                return ENOMEM;
            }
        }


        if (!newline)
            while (((gobble = getc(fp)) != EOF) && gobble != '\n');

        if( !(linebuf = (char *) calloc (BUFSIZ, sizeof(char)))) return ENOMEM;
    }

    buf_out[count] = NULL;
    *princ_list = buf_out;
    fclose(fp);
    return 0;
}
