gwy_ascii_strcase_hash(gconstpointer v)
{
    const signed char *p;
    guint32 h = 5381;

    for (p = v; *p != '\0'; p++)
        h = (h << 5) + h + TOLOWER(*p);

    return h;
}
