dht_lookup_directory (call_frame_t *frame, xlator_t *this, loc_t *loc)
{
        int           call_cnt = 0;
        int           i = 0;
        dht_conf_t   *conf = NULL;
        dht_local_t  *local = NULL;
        int           ret = 0;

        GF_VALIDATE_OR_GOTO ("dht", frame, out);
        GF_VALIDATE_OR_GOTO ("dht", this, unwind);
        GF_VALIDATE_OR_GOTO ("dht", frame->local, unwind);
        GF_VALIDATE_OR_GOTO ("dht", this->private, unwind);
        GF_VALIDATE_OR_GOTO ("dht", loc, unwind);

        conf = this->private;
        local = frame->local;

        call_cnt        = conf->subvolume_cnt;
        local->call_cnt = call_cnt;

        local->layout = dht_layout_new (this, conf->subvolume_cnt);
        if (!local->layout) {
                goto unwind;
        }

        if (local->xattr != NULL) {
                dict_unref (local->xattr);
                local->xattr = NULL;
        }

        if (!uuid_is_null (local->gfid)) {
                ret = dict_set_static_bin (local->xattr_req, "gfid-req",
                                           local->gfid, 16);
                if (ret)
                        gf_log (this->name, GF_LOG_WARNING,
                                "%s: failed to set gfid", local->loc.path);
        }

        for (i = 0; i < call_cnt; i++) {
                STACK_WIND (frame, dht_lookup_dir_cbk,
                            conf->subvolumes[i],
                            conf->subvolumes[i]->fops->lookup,
                            &local->loc, local->xattr_req);
        }
        return 0;
unwind:
        DHT_STACK_UNWIND (lookup, frame, -1, ENOMEM, NULL, NULL, NULL, NULL);
out:
        return 0;

}
