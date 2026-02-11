dht_layout_anomalies (xlator_t *this, loc_t *loc, dht_layout_t *layout,
                      uint32_t *holes_p, uint32_t *overlaps_p,
                      uint32_t *missing_p, uint32_t *down_p, uint32_t *misc_p,
                      uint32_t *no_space_p)
{
        uint32_t    overlaps = 0;
        uint32_t    missing  = 0;
        uint32_t    down     = 0;
        uint32_t    misc     = 0;
        uint32_t    hole_cnt = 0;
        uint32_t    overlap_cnt = 0;
        int         i = 0;
        int         ret = 0;
        uint32_t    prev_stop = 0;
        uint32_t    last_stop = 0;
        char        is_virgin = 1;
        uint32_t    no_space  = 0;


        last_stop = layout->list[0].start - 1;
        prev_stop = last_stop;

        for (i = 0; i < layout->cnt; i++) {
                switch (layout->list[i].err) {
                case -1:
                case ENOENT:
                        missing++;
                        continue;
                case ENOTCONN:
                        down++;
                        continue;
                case ENOSPC:
                        no_space++;
                        continue;
                case 0:


                        if (layout->list[i].start == layout->list[i].stop) {
                                continue;
                        }
                        break;
                default:
                        misc++;
                        continue;
                 }

                is_virgin = 0;

                if ((prev_stop + 1) < layout->list[i].start) {
                        hole_cnt++;
                }

                if ((prev_stop + 1) > layout->list[i].start) {
                        overlap_cnt++;
                        overlaps += ((prev_stop + 1) - layout->list[i].start);
                }
                prev_stop = layout->list[i].stop;
        }

        if ((last_stop - prev_stop) || is_virgin)
                hole_cnt++;

        if (holes_p)
                *holes_p = hole_cnt;

        if (overlaps_p)
                *overlaps_p = overlap_cnt;

        if (missing_p)
                *missing_p = missing;

        if (down_p)
                *down_p = down;

        if (misc_p)
                *misc_p = misc;

        if (no_space_p)
                *no_space_p = no_space;

        return ret;
}
