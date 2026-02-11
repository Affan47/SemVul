switch_create (call_frame_t *frame, xlator_t *this,
               loc_t *loc, int32_t flags, mode_t mode,
               mode_t umask, fd_t *fd, dict_t *params)
{
        dht_local_t *local = NULL;
        dht_conf_t  *conf  = NULL;
        xlator_t    *subvol = NULL;
        xlator_t    *avail_subvol = NULL;
        int          op_errno = -1;

        VALIDATE_OR_GOTO (frame, err);
        VALIDATE_OR_GOTO (this, err);
        VALIDATE_OR_GOTO (loc, err);

        conf  = this->private;

        dht_get_du_info (frame, this, loc);

        local = dht_local_init (frame, loc, fd, GF_FOP_CREATE);
        if (!local) {
                op_errno = ENOMEM;
                goto err;
        }

        subvol = dht_subvol_get_hashed (this, loc);
        if (!subvol) {
                gf_log (this->name, GF_LOG_DEBUG,
                        "no subvolume in layout for path=%s",
                        loc->path);
                op_errno = ENOENT;
                goto err;
        }

        avail_subvol = get_switch_matching_subvol (loc->path, conf, subvol);
        if (dht_is_subvol_filled (this, avail_subvol)) {
                avail_subvol =
                        dht_free_disk_available_subvol (this, avail_subvol,
                                                        local);
        }

        if (subvol != avail_subvol) {

                local->mode = mode;
                local->flags = flags;
                local->umask = umask;
                local->cached_subvol = avail_subvol;
                dht_linkfile_create (frame,
                                     switch_create_linkfile_create_cbk,
                                     avail_subvol, subvol, loc);
                return 0;
        }

        gf_log (this->name, GF_LOG_TRACE,
                "creating %s on %s", loc->path, subvol->name);

        STACK_WIND (frame, dht_create_cbk,
                    subvol, subvol->fops->create,
                    loc, flags, mode, umask, fd, params);

        return 0;

err:
        op_errno = (op_errno == -1) ? errno : op_errno;
        DHT_STACK_UNWIND (create, frame, -1, op_errno,
                          NULL, NULL, NULL, NULL, NULL, NULL);

        return 0;
}
