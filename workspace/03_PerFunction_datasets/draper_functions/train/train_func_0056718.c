verify_int( char* arg_str, int* value ) {
    int result = 0;
    regex_t regex;
    regmatch_t match_list[MAX_MATCHES];

    if (!arg_str || !value) {
        goto unclean;
    }
    if (regcomp(&regex, "^[+]?[0-9]+$", REG_EXTENDED | REG_NEWLINE)) {
        goto unclean;
    }
    if (regexec(&regex, arg_str, (size_t)MAX_MATCHES, match_list, 0)) {
        goto unclean;
    }
    *value = atoi(arg_str);
    result = 1;

 unclean:
    regfree(&regex);
    return result;
}
