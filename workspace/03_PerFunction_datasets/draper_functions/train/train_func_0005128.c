orte_getline(FILE *fp)
{
    char *ret, *buff;
    char input[1024];
    int i;

    ret = fgets(input, 1024, fp);
    if (NULL != ret) {

        for (i=strlen(input)-2; i > 0; i--) {
            if (input[i] != ' ') {
                input[i+1] = '\0';
                break;
            }
        }
        buff = strdup(input);
        return buff;
    }

    return NULL;
}
