fractional(jsdouble *result, const jschar *s, size_t *i, size_t limit)
{
    jsdouble factor = 0.1;
    size_t init = *i;
    *result = 0.0;
    while (*i < limit &&
           ('0' <= s[*i] && s[*i] <= '9')) {
        *result += (s[*i] - '0') * factor;
        factor *= 0.1;
        ++(*i);
    }
    return (*i != init);
}
