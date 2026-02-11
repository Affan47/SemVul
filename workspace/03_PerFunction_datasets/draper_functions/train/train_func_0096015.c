search_for(unsigned char marker, char **cursor)
{
    while (**cursor && **cursor != marker)
    {
        (*cursor)++;
    }

    if (**cursor == '\0')
    {
        return FALSE;
    }
    else
    {
        (*cursor)++;
        return TRUE;
    }
}
