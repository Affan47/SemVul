stream_compact(stream * s, bool always)
{
    if (s->cursor.r.ptr >= s->cbuf && (always || s->end_status >= 0)) {
        uint dist = s->cursor.r.ptr + 1 - s->cbuf;

        memmove(s->cbuf, s->cursor.r.ptr + 1,
                (uint) (s->cursor.r.limit - s->cursor.r.ptr));
        s->cursor.r.ptr = s->cbuf - 1;
        s->cursor.r.limit -= dist;
        s->position += dist;
    }
}
