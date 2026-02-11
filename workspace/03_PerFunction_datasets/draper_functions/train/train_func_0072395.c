dht_unlink (call_frame_t *frame, xlator_t *this, loc_t *loc, int xflag,
            dict_t *xdata)
{
        xlator_t    *cached_subvol = NULL;
        xlator_t    *hashed_subvol = NULL;
        int          op_errno = -1;
        dht_local_t *local = NULL;

        VALIDATE_OR_GOTO (frame, err);
        VALIDATE_OR_GOTO (this, err);
        VALIDATE_OR_GOTO (loc, err);

        if (dht_filter_loc_subvol_key (this, loc, &local->loc,
                                       &cached_subvol)) {
                gf_log (this->name, GF_LOG_INFO,
                        "unlinking %s on %s (given path %s)",
                        local->loc.path, cached_subvol->name, loc->path);
                STACK_WIND (frame, dht_unlink_cbk,
                            cached_subvol, cached_subvol->fops->unlink,
                            &local->loc, xflag, xdata);
                goto done;
        }

        local = dht_local_init (frame, loc, NULL, GF_FOP_UNLINK);
        if (!local) {
                op_errno = ENOMEM;

                goto err;
        }

        hashed_subvol = dht_subvol_get_hashed (this, loc);
        if (!hashed_subvol) {
                gf_log (this->name, GF_LOG_DEBUG,
                        "no subvolume in layout for path=%s",
                        loc->path);
                op_errno = EINVAL;
                goto err;
        }

        cached_subvol = local->cached_subvol;
        if (!cached_subvol) {
                gf_log (this->name, GF_LOG_DEBUG,
                        "no cached subvolume for path=%s", loc->path);
                op_errno = EINVAL;
                goto err;
        }

        local->flags = xflag;
        if (hashed_subvol != cached_subvol) {
                STACK_WIND (frame, dht_unlink_linkfile_cbk,
                            hashed_subvol, hashed_subvol->fops->unlink, loc,
                            xflag, xdata);
        } else {
                STACK_WIND (frame, dht_unlink_cbk,
                            cached_subvol, cached_subvol->fops->unlink, loc,
                            xflag, xdata);
        }
done:
        return 0;
err:
        op_errno = (op_errno == -1) ? errno : op_errno;
        DHT_STACK_UNWIND (unlink, frame, -1, op_errno, NULL, NULL, NULL);

        return 0;
}
