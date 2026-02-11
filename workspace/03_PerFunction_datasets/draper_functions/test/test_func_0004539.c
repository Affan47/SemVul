fs_strchomp(char *string) {
    size_t len;

    if (string == NULL) {
        return NULL;
    }

    len = strlen(string);
    while (len--) {
        if (fs_ascii_isspace((unsigned char) string[len])) string[len] = '\0';
        else
            break;
    }

    return string;
}
