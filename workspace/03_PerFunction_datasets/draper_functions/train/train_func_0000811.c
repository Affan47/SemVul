squaretrans_pow2(mpd_uint_t *matrix, mpd_size_t size)
{
    mpd_uint_t buf1[SIDE*SIDE];
    mpd_uint_t buf2[SIDE*SIDE];
    mpd_uint_t *to, *from;
    mpd_size_t b = size;
    mpd_size_t r, c;
    mpd_size_t i;

    while (b > SIDE) b >>= 1;

    for (r = 0; r < size; r += b) {

        for (c = r; c < size; c += b) {

            from = matrix + r*size + c;
            to = buf1;
            for (i = 0; i < b; i++) {
                memcpy(to, from, b*(sizeof *to));
                from += size;
                to += b;
            }
            squaretrans(buf1, b);

            if (r == c) {
                to = matrix + r*size + c;
                from = buf1;
                for (i = 0; i < b; i++) {
                    memcpy(to, from, b*(sizeof *to));
                    from += b;
                    to += size;
                }
                continue;
            }
            else {
                from = matrix + c*size + r;
                to = buf2;
                for (i = 0; i < b; i++) {
                    memcpy(to, from, b*(sizeof *to));
                    from += size;
                    to += b;
                }
                squaretrans(buf2, b);

                to = matrix + c*size + r;
                from = buf1;
                for (i = 0; i < b; i++) {
                    memcpy(to, from, b*(sizeof *to));
                    from += b;
                    to += size;
                }

                to = matrix + r*size + c;
                from = buf2;
                for (i = 0; i < b; i++) {
                    memcpy(to, from, b*(sizeof *to));
                    from += b;
                    to += size;
                }
            }
        }
    }

}
