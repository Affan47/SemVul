mkstar(char *string)
{
    char *starred = NULL;
    int i;

    int len = strlen(string) + 1;

    if ((starred = malloc(len)) == NULL) {
        perror("mkstar()");
        exit(1);
    }

    for (i = 0; i < len-1; i++)
        starred[i] = '*';

    starred[len] = '\0';

    return starred;
}
