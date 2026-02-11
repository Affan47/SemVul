irc_parse_message(const char *words[],
                       const char **prefix, const char **command,
                       size_t *parameters_offset) {
    size_t w = 1;
    if (prefix) *prefix = NULL;
    if (command) *command = NULL;


    if (words[w][0] == ':') {
        if (prefix) *prefix = &words[w][1];
        w++;
    }


    if (words[w][0] == '\0') return false;
    if (command) *command = words[w];
    w++;

    *parameters_offset = w;
    return true;
}
