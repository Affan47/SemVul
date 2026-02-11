strbuf_init(strbuf_t *s, int len, lua_State *l, int max_size)
{
    int size;

    if (len <= 0)
        if (max_size > 0 && max_size < STRBUF_DEFAULT_SIZE) {
            size = max_size;
        } else {
            size = STRBUF_DEFAULT_SIZE;
        }
    else
        size = len + 1;

    s->buf = NULL;
    s->size = size;
    s->length = 0;
    s->increment = STRBUF_DEFAULT_INCREMENT;
    s->dynamic = 0;
    s->reallocs = 0;
    s->debug = 0;
    s->max_size = max_size;
    s->lua = l;

    s->buf = malloc(size);
    if (!s->buf)
        luaL_error(l, "strbuf_init out of memory");

    strbuf_ensure_null(s);
}
