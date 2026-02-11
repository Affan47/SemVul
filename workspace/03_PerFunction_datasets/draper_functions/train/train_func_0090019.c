dht_fix_dir_xattr (call_frame_t *frame, loc_t *loc, dht_layout_t *layout)
{
        dht_local_t *local = NULL;
        int          i = 0;
        int          count = 0;
        xlator_t    *this = NULL;
        dht_conf_t  *conf = NULL;
        dht_layout_t *dummy = NULL;

        local = frame->local;
        this = frame->this;
        conf = this->private;

        gf_log (this->name, GF_LOG_DEBUG,
                "writing the new range for all subvolumes");

        local->call_cnt = count = conf->subvolume_cnt;

        for (i = 0; i < layout->cnt; i++) {
                dht_selfheal_dir_xattr_persubvol (frame, loc, layout, i, NULL);

                if (--count == 0)
                        goto out;
        }


        dummy = dht_layout_new (this, 1);
        if (!dummy)
                goto out;
        for (i = 0; i < conf->subvolume_cnt; i++) {
                if (_gf_false ==
                    dht_is_subvol_in_layout (layout, conf->subvolumes[i])) {
                        dht_selfheal_dir_xattr_persubvol (frame, loc, dummy, 0,
                                                          conf->subvolumes[i]);
                        if (--count == 0)
                                break;
                }
        }

        dht_layout_unref (this, dummy);
out:
        return 0;
}
