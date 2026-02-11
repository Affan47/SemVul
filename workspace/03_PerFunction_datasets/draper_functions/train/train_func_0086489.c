skip_space (const char **pos)
{
        const char *p = *pos;

        while (g_ascii_isspace (*p))
                p++;

        *pos = p;

        return !(*p == '\0');
}
