getinput(const char *message, char *defvalue)
{
    printf("%s [%s]: ", message, (defvalue == NULL) ? "" : defvalue);
    fflush(stdout);

    char *line = NULL;
    char *p = NULL;

    if ((line = malloc(MAXBUF+1)) == NULL) {
        perror("getinput() could not malloc");
        exit(1);
    }

    p = fgets(line, MAXBUF, stdin);

    if (p != NULL) {
        int last = strlen(line) - 1;

        if (line[0] == '\n') {
            if (defvalue != NULL)
                p = strdup(defvalue);
        }

        if (strchr(line, '\n') == NULL) {

            fprintf(stderr, "Input line would not fit in buffer. Exiting.");
            exit(1);
        }


        if (line[last] == '\n')
            line[last] = '\0';

    }

    return p;
}
