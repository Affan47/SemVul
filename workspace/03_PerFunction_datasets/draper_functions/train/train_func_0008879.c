strip_d_macro(char *token) {
    if ((strncmp("d(", token, 2) == 0) && (*(end_of_token(token) - 1) == ')')) {
        memmove(token, token + 2, strlen(token) - 2 + 1);
        *(end_of_token(token) - 1) = '\0';
    }
    return token;
}
