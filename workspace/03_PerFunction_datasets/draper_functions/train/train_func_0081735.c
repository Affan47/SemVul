make_list_like(char *input) {
    char *p, tmp[MAX_BUF];
    int i;
    if (!input || strlen(input) > MAX_BUF-5)
        return;


    strncpy(tmp, input, MAX_BUF-5);

    for (i = strlen(tmp); !isalnum(tmp[i]) && i >= 0; i--)
        tmp[i] = '\0';
    strcat(tmp, ".");

    p = strrchr(tmp, ',');
    if (p) {
        *p = '\0';
        strcpy(input, tmp);
        p++;
        strcat(input, " and");
        strcat(input, p);
    } else
        strcpy(input, tmp);
    return;
}
