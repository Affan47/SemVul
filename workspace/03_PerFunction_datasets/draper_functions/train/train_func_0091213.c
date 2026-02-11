s_12_8_process(stream_state * st, stream_cursor_read * pr,
               stream_cursor_write * pw, bool last)
{
    BEGIN_1248;

    n = ss->samples_per_row;
    status = 0;
    for (; rlimit - p >= 2; ++q) {
        if (q >= wlimit) {
            status = 1;
            break;
        }
        if (left == 0)
            left = n;
        if ((n - left) & 1) {
            q[1] = (byte)((p[1] << 4) | (p[2] >> 4));
            p += 2, --left;
        } else {
            q[1] = *++p;
            if (!--left)
                ++p;
        }
    }

    END_1248;
}
