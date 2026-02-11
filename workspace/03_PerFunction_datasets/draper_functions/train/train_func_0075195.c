update_state(hlmojo_IncludeState *s, int eoi, const uchar *cur,
                          const uchar *tok, const Token val)
{
    if (eoi)
    {
        s->bytes_left = 0;
        s->source = (const char *) s->source_base + s->orig_length;
        if ( (tok >= sentinel) && (tok < (sentinel+YYMAXFILL)) )
            s->token = s->source;
        else
            s->token = (const char *) tok;
    }
    else
    {
        s->bytes_left -= (unsigned int) (cur - ((const uchar *) s->source));
        s->source = (const char *) cur;
        s->token = (const char *) tok;
    }
    s->tokenlen = (unsigned int) (s->source - s->token);
    s->tokenval = val;
    return val;
}
