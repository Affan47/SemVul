deflate_stored(s, flush)
    deflate_state *s;
    int flush;
{


    ulg max_block_size = 0xffff;
    ulg max_start;

    if (max_block_size > s->pending_buf_size - 5) {
        max_block_size = s->pending_buf_size - 5;
    }


    for (;;) {

        if (s->lookahead <= 1) {

            Assert(s->strstart < s->w_size+MAX_DIST(s) ||
                   s->block_start >= (long)s->w_size, "slide too late");

            fill_window(s);
            if (s->lookahead == 0 && flush == Z_NO_FLUSH) return need_more;

            if (s->lookahead == 0) break;
        }
        Assert(s->block_start >= 0L, "block gone");

        s->strstart += s->lookahead;
        s->lookahead = 0;


        max_start = s->block_start + max_block_size;
        if (s->strstart == 0 || (ulg)s->strstart >= max_start) {

            s->lookahead = (uInt)(s->strstart - max_start);
            s->strstart = (uInt)max_start;
            FLUSH_BLOCK(s, 0);
        }


        if (s->strstart - (uInt)s->block_start >= MAX_DIST(s)) {
            FLUSH_BLOCK(s, 0);
        }
    }
    FLUSH_BLOCK(s, flush == Z_FINISH);
    return flush == Z_FINISH ? finish_done : block_done;
}
