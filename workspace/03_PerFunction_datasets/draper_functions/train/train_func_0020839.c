ndigits(size_t n, size_t *result, const jschar *s, size_t* i, size_t limit)
{
    size_t init = *i;

    if (digits(result, s, i, JS_MIN(limit, init+n)))
        return ((*i - init) == n);

    *i = init;
    return JS_FALSE;
}
