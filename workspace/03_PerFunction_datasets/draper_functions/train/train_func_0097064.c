s_PNGPE_process(stream_state * st, stream_cursor_read * pr,
                stream_cursor_write * pw, bool last)
{
    stream_PNGP_state *const ss = (stream_PNGP_state *) st;
    int bpp = ss->bpp;
    int status = 0;

    while (pr->ptr < pr->limit) {
        uint count;

        if (ss->row_left == 0) {

            int predictor;

            if (pw->ptr >= pw->limit) {
                status = 1;
                break;
            }
            predictor =
                (ss->Predictor == cOptimum ?
                 optimum_predictor(st, pr) :
                 ss->Predictor);
            *++(pw->ptr) = (byte) predictor - cNone;
            ss->case_index = predictor + cEncode;
            ss->row_left = ss->row_count;
            memset(ss->prev, 0, bpp);
            continue;
        }
        count = s_pngp_count(st, pr, pw);
        if (count == 0) {

            status = 1;
            break;
        } {
            byte *up = ss->prev_row + bpp + ss->row_count - ss->row_left;
            uint n = min(count, bpp);


            s_pngp_process(st, pw, ss->prev, pr, up - bpp, up, n);
            if (ss->row_left == 0) {
                if (ss->prev_row) {
                    memcpy(up - bpp, ss->prev, bpp);
                    memcpy(up, pr->ptr - (n - 1), n);
                }
                continue;
            }
            if (ss->prev_row)
                memcpy(up - bpp, ss->prev, n);
            if (n < bpp) {


                int prev_left = bpp - n;

                memmove(ss->prev, ss->prev + n, prev_left);
                memcpy(ss->prev + prev_left, pr->ptr - (n - 1), n);
                if (pw->ptr >= pw->limit && pr->ptr < pr->limit)
                    status = 1;
                break;
            }


            count -= bpp;
            s_pngp_process(st, pw, pr->ptr - (bpp - 1), pr,
                           up, up + bpp, count);
            memcpy(ss->prev, pr->ptr - (bpp - 1), bpp);
            if (ss->prev_row) {
                memcpy(up, pr->ptr - (bpp + count - 1), count);
                if (ss->row_left == 0)
                    memcpy(up + count, ss->prev, bpp);
            }
        }
    }
    return status;
}
