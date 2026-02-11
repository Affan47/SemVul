epr_find_first_not_white(const char* str)
{
    int i;
    char white[] = {" "};

    for (i = 0; i < (int)strlen(str); i ++) {
        if (strchr(white, str[i]) == NULL) return i;
    }
    return (int)strlen(str);
}
