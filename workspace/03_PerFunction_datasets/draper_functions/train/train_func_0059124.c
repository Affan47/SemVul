dht_selfheal_directory (call_frame_t *frame, dht_selfheal_dir_cbk_t dir_cbk,
                        loc_t *loc, dht_layout_t *layout)
{
        dht_local_t *local    = NULL;
        uint32_t     down     = 0;
        uint32_t     misc     = 0;
        int          ret      = 0;
        xlator_t    *this     = NULL;

        local = frame->local;
        this = frame->this;

        dht_layout_anomalies (this, loc, layout,
                              &local->selfheal.hole_cnt,
                              &local->selfheal.overlaps_cnt,
                              NULL, &local->selfheal.down,
                              &local->selfheal.misc, NULL);

        down     = local->selfheal.down;
        misc     = local->selfheal.misc;

        local->selfheal.dir_cbk = dir_cbk;
        local->selfheal.layout = dht_layout_ref (this, layout);

        if (down) {
                gf_log (this->name, GF_LOG_WARNING,
                        "%d subvolumes down -- not fixing", down);
                ret = 0;
                goto sorry_no_fix;
        }

        if (misc) {
                gf_log (this->name, GF_LOG_WARNING,
                        "%d subvolumes have unrecoverable errors", misc);
                ret = 0;
                goto sorry_no_fix;
        }

        dht_layout_sort_volname (layout);
        ret = dht_selfheal_dir_getafix (frame, loc, layout);

        if (ret == -1) {
                gf_log (this->name, GF_LOG_WARNING,
                        "not able to form layout for the directory");
                goto sorry_no_fix;
        }

        dht_selfheal_dir_mkdir (frame, loc, layout, 0);

        return 0;

sorry_no_fix:

        dht_selfheal_dir_finish (frame, this, ret);

        return 0;
}
