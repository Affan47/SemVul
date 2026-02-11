utf8_iterate(const char *buffer, size_t bufsize, int32_t *codepoint)
{
    size_t count;
    int32_t value;

    if(!bufsize)
        return buffer;

    count = utf8_check_first(buffer[0]);
    if(count <= 0)
        return NULL;

    if(count == 1)
        value = (unsigned char)buffer[0];
    else
    {
        if(count > bufsize || !utf8_check_full(buffer, count, &value))
            return NULL;
    }

    if(codepoint)
        *codepoint = value;

    return buffer + count;
}
