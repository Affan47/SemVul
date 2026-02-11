s_8_N_process(stream_state * st, stream_cursor_read * pr,
              stream_cursor_write * pw, bool last)
{
    BEGIN_1248;

    switch (ss->bits_per_sample) {

        case 1:{
                FOREACH_8_N(out, 8)
        case 8:
                out = p[8] >> 7;
        case 7:
                out |= (p[7] >> 7) << 1;
        case 6:
                out |= (p[6] >> 7) << 2;
        case 5:
                out |= (p[5] >> 7) << 3;
        case 4:
                out |= (p[4] >> 7) << 4;
        case 3:
                out |= (p[3] >> 7) << 5;
        case 2:
                out |= (p[2] >> 7) << 6;
        case 1:
                out |= p[1] & 0x80;
                END_FOREACH_8_N;
            }
            break;

        case 2:{
                FOREACH_8_N(out, 4)
        case 4:
                out |= p[4] >> 6;
        case 3:
                out |= (p[3] >> 6) << 2;
        case 2:
                out |= (p[2] >> 6) << 4;
        case 1:
                out |= p[1] & 0xc0;
                END_FOREACH_8_N;
            }
            break;

        case 4:{
                FOREACH_8_N(out, 2)
        case 2:
                out |= p[2] >> 4;
        case 1:
                out |= p[1] & 0xf0;
                END_FOREACH_8_N;
            }
            break;

        default:
            return ERRC;
    }

    END_1248;
}
