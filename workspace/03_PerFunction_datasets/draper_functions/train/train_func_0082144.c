read_string_full (void* (*alloc_fn)(size_t n))
{
    int length;
    char *value;

    if (read_data (&length, sizeof (length)) <= 0)
        return NULL;
    if (length < 0)
        return NULL;
    if (length > MAX_STRING_LENGTH)
    {
        g_printerr ("Invalid string length %d from daemon\n", length);
        return NULL;
    }

    value = (*alloc_fn) (sizeof (char) * (length + 1));
    read_data (value, length);
    value[length] = '\0';

    return value;
}
