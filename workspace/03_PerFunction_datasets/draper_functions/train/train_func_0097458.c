dht_selfheal_dir_getafix (call_frame_t *frame, loc_t *loc,
                          dht_layout_t *layout)
{
        dht_local_t *local = NULL;
        uint32_t     holes = 0;
        int          ret = -1;
        int          i = -1;
        uint32_t     overlaps = 0;

        local = frame->local;

        holes = local->selfheal.hole_cnt;
        overlaps = local->selfheal.overlaps_cnt;

        if (holes || overlaps) {
                dht_selfheal_layout_new_directory (frame, loc, layout);
                ret = 0;
        }

        for (i = 0; i < layout->cnt; i++) {

                if (layout->list[i].err == ENOENT) {
                        ret = 0;
                        break;
                }
        }


        return ret;
}
