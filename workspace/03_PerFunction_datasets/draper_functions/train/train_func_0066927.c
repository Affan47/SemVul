skip_quotes(const char **string) {
    SKIP_CHAR(string);
    while (**string != '\"') {
        if (**string == '\0')
            return;
        if (**string == '\\') {
            SKIP_CHAR(string);
            if (**string == '\0')
                return;
        }
        SKIP_CHAR(string);
    }
    SKIP_CHAR(string);
}
