s_RLD_process(stream_state * st, stream_cursor_read * pr,
              stream_cursor_write * pw, bool last)
{
    stream_RLD_state *const ss = (stream_RLD_state *) st;
    register const byte *p = pr->ptr;
    register byte *q = pw->ptr;
    const byte *rlimit = pr->limit;
    byte *wlimit = pw->limit;
    int left;
    int status = 0;

top:
    if ((left = ss->copy_left) > 0) {


        uint avail = wlimit - q;
        int copy_status = 1;

        if (left > avail)
            left = avail;
        if (ss->copy_data >= 0)
            memset(q + 1, ss->copy_data, left);
        else {
            avail = rlimit - p;
            if (left >= avail) {
                copy_status = 0;
                left = avail;
            }
            memcpy(q + 1, p + 1, left);
            p += left;
        }
        q += left;
        if ((ss->copy_left -= left) > 0) {
            status = copy_status;
            goto x;
        }
    }
    while (p < rlimit) {
        int b = *++p;

        if (b < 128) {
            if (++b > rlimit - p || b > wlimit - q) {
                ss->copy_left = b;
                ss->copy_data = -1;
                goto top;
            }
            memcpy(q + 1, p + 1, b);
            p += b;
            q += b;
        } else if (b == 128) {
            if (ss->EndOfData) {
                status = EOFC;
                break;
            }
        } else if (p == rlimit) {
            p--;
            break;
        } else if ((b = 257 - b) > wlimit - q) {
            ss->copy_left = b;
            ss->copy_data = *++p;
            goto top;
        } else {
            memset(q + 1, *++p, b);
            q += b;
        }
    }
x:  pr->ptr = p;
    pw->ptr = q;
    return status;
}
