create_value_expand_variables(std::map<std::string, std::string>& setup,
        const char* val_begin,
        char* buffer2) {
    const char* p = val_begin;
    bool escape_on = false;
    while (*p!= '\0') {
        if (*p == '\\') {
            if (escape_on) escape_on = false;
            else escape_on = true;
            *buffer2++ = *p++;
            continue;
        }
        if (*p == '\n') {*buffer2++ = '\0'; return true;}

        if (*p == '$' && !escape_on) {
            escape_on = false;
            if (*(p+1)=='{' || *(p+1) == '(') {
                char to_find = *(p+1)=='{' ? '}' : ')';
                p+=2;
                if (!process_variable_expansion(setup, p, buffer2, to_find))
                    return false;
                else
                    continue;
            }
        }

        escape_on = false;
        *buffer2++ = *p++;
    }

    *buffer2 = '\0';
    return true;
}
