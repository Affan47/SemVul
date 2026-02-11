keyval_append_error(char * e) {
    if (error) {
        error = realloc(error, strlen(error) + strlen(e) + 1);
        strcat(error, e);
    } else {
        error = strdup(e);
    }
}
