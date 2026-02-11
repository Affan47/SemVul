highlightCode3(Scope *sc, OutBuffer *buf, utf8_t *p, utf8_t *pend)
{
    for (; p < pend; p++)
    {   const char *s = sc->module->escapetable->escapeChar(*p);
        if (s)
            buf->writestring(s);
        else
            buf->writeByte(*p);
    }
}
