__archive_string_append(struct archive_string *as, const char *p, size_t s)
{
    if (__archive_string_ensure(as, as->length + s + 1) == NULL)
        __archive_errx(1, "Out of memory");
    memcpy(as->s + as->length, p, s);
    as->s[as->length + s] = 0;
    as->length += s;
    return (as);
}
