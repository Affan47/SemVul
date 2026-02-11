get_token(interface_defn * ifd UNUSED, char **pparam, int argc, char **argv)
{
    if (argc == 0)
        return;

    int token_no;
    if (argc == 1) {
        token_no = 0;
    } else {
        token_no = atoi(argv[1]);
    }

    char *s = strdup(*pparam);
    char *token = strtok(s, argv[0]);
    while (token_no > 0) {
        token = strtok(NULL, argv[0]);
        token_no--;
    }
    if (token) {
        strcpy(*pparam, token);
    } else {
        if (argc == 3) {
            *pparam = realloc(*pparam, strlen(argv[2]) + 1);
            if (*pparam == NULL)
                return;
            strcpy(*pparam, argv[2]);
        }
    }
    free(s);
}
