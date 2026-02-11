has_non_ASCII(const wchar_t *wp)
{
    if (wp == NULL)
        return (1);
    while (*wp != L'\0' && *wp < 128)
        wp++;
    return (*wp != L'\0');
}
