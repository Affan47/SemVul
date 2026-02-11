_ircprot_skip_spaces(char *ptr) {
#ifdef OLD_RFC1459_PARAM_SPACE
    while (*ptr && (*ptr == ' ')) ptr++;
#else
    if (*ptr && (*ptr == ' ')) ptr++;
#endif

    return ptr;
}
