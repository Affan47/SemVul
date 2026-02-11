sreadbuf(stream * s, stream_cursor_write * pbuf)
{
    stream *prev = 0;
    stream *curr = s;
    int status;

    for (;;) {
        stream *strm;
        stream_cursor_write *pw;
        byte *oldpos;

        for (;;) {
            stream_cursor_read cr;
            stream_cursor_read *pr;
            int left;
            bool eof;

            strm = curr->strm;
            if (strm == 0) {
                cr.ptr = 0, cr.limit = 0;
                pr = &cr;
                left = 0;
                eof = false;
            } else {
                pr = &strm->cursor.r;
                left = sbuf_min_left(strm);
                left = min(left, pr->limit - pr->ptr);
                pr->limit -= left;
                eof = strm->end_status == EOFC;
            }
            pw = (prev == 0 ? pbuf : &curr->cursor.w);
            if_debug4m('s', s->memory, "[s]read process 0x%lx, nr=%u, nw=%u, eof=%d\n",
                       (ulong) curr, (uint) (pr->limit - pr->ptr),
                       (uint) (pw->limit - pw->ptr), eof);
            oldpos = pw->ptr;
            status = (*curr->procs.process) (curr->state, pr, pw, eof);
            pr->limit += left;
            if_debug5m('s', s->memory, "[s]after read 0x%lx, nr=%u, nw=%u, status=%d, position=%"PRId64"\n",
                       (ulong) curr, (uint) (pr->limit - pr->ptr),
                       (uint) (pw->limit - pw->ptr), status, s->position);
            if (strm == 0 || status != 0)
                break;
            if (strm->end_status < 0) {
                if (strm->end_status != EOFC || pw->ptr == oldpos)
                    status = strm->end_status;
                break;
            }
            MOVE_AHEAD(curr, prev);
            stream_compact(curr, false);
        }


        if ((strm != 0 || curr->file) && status == EOFC &&
            curr->cursor.r.ptr >= curr->cursor.r.limit &&
            curr->close_at_eod &&
            prev == 0
            ) {
            int cstat = sclose(curr);

            if (cstat != 0)
                status = cstat;
        }

        curr->end_status = (status >= 0 ? 0 : status);
        if (prev == 0)
            return status;
        MOVE_BACK(curr, prev);
    }
}
