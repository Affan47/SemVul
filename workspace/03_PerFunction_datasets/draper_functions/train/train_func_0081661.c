register_string(char *s)
{
    *(tab.last++) = s;
    if (tab.last == tab.end) resize_string_table();
}
