getword (void)
{
    char *p, *q;

    p = _lp ? _lp : _text;
    if (_lc) p++;
    while (*p && isspace (*p)) p++;
    q = p;
    while (*p && ! isspace (*p)) p++;
    _lc = *p;
    _lp = p;
    *p = 0;
    return *q ? q : 0;
}
