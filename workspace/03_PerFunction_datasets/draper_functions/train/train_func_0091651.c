is_last_word(const char* line, const char* word, int len)
{
    const char* t;

    ASSERT(line);
    ASSERT(word);
    ASSERT(len > 0);

    t = line + strlen(line);

    while(t > line && isspace(*(t - 1)))
        --t;

    if(t - len < line)
        return 0;

    return strncasecmp(t - len, word, len) == 0;
}
