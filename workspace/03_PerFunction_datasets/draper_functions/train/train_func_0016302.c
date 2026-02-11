deflate_huff(s, flush)
    deflate_state *s;
    int flush;
{
    int bflush;

    for (;;) {

        if (s->lookahead == 0) {
            fill_window(s);
            if (s->lookahead == 0) {
                if (flush == Z_NO_FLUSH)
                    return need_more;
                break;
            }
        }


        s->match_length = 0;
        Tracevv((stderr,"%c", s->window[s->strstart]));
        _tr_tally_lit (s, s->window[s->strstart], bflush);
        s->lookahead--;
        s->strstart++;
        if (bflush) FLUSH_BLOCK(s, 0);
    }
    FLUSH_BLOCK(s, flush == Z_FINISH);
    return flush == Z_FINISH ? finish_done : block_done;
}
