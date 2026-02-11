handle_size(char *params)
{


    int n;
    char *extra;

    if(params == NULL) {
        return -1;
    }


    extra = (char *)malloc(strlen(params) * sizeof(char));
    if(sscanf(params, "%d %s", &n, extra) < 2) {
        free(extra);
        return -1;
    }


    struct stat buffer;
    if(stat(extra, &buffer) || buffer.st_size <= n) {
        free(extra);
        return -1;
    }

    free(extra);
    return 5;
}
