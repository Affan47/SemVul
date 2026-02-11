dht_readdirp_cbk (call_frame_t *frame, void *cookie, xlator_t *this, int op_ret,
                  int op_errno, gf_dirent_t *orig_entries, dict_t *xdata)
{
        dht_local_t  *local = NULL;
        gf_dirent_t   entries;
        gf_dirent_t  *orig_entry = NULL;
        gf_dirent_t  *entry = NULL;
        call_frame_t *prev = NULL;
        xlator_t     *next_subvol = NULL;
        off_t         next_offset = 0;
        int           count = 0;
        dht_layout_t *layout = 0;
        dht_conf_t   *conf   = NULL;
        xlator_t     *subvol = 0;

        INIT_LIST_HEAD (&entries.list);
        prev = cookie;
        local = frame->local;
        conf  = this->private;

        if (op_ret < 0)
                goto done;

        if (!local->layout)
                local->layout = dht_layout_get (this, local->fd->inode);

        layout = local->layout;

        list_for_each_entry (orig_entry, (&orig_entries->list), list) {
                next_offset = orig_entry->d_off;
                if ((check_is_dir (NULL, (&orig_entry->d_stat), NULL) &&
                     (prev->this != dht_first_up_subvol (this))) ||
                    check_is_linkfile (NULL, (&orig_entry->d_stat),
                                       orig_entry->dict)) {
                        continue;
                }

                entry = gf_dirent_for_name (orig_entry->d_name);
                if (!entry) {

                        goto unwind;
                }


                if (conf->search_unhashed == GF_DHT_LOOKUP_UNHASHED_AUTO) {
                        subvol = dht_layout_search (this, layout,
                                                    orig_entry->d_name);
                        if (!subvol || (subvol != prev->this)) {


                                layout->search_unhashed++;
                        }
                }

                dht_itransform (this, prev->this, orig_entry->d_off,
                                &entry->d_off);

                entry->d_stat = orig_entry->d_stat;
                entry->d_ino  = orig_entry->d_ino;
                entry->d_type = orig_entry->d_type;
                entry->d_len  = orig_entry->d_len;

                list_add_tail (&entry->list, &entries.list);
                count++;
        }
        op_ret = count;


        if (prev->this != dht_last_up_subvol (this))
                op_errno = 0;

done:
        if (count == 0) {


                if (next_offset == 0) {
                        next_subvol = dht_subvol_next (this, prev->this);
                } else {
                        next_subvol = prev->this;
                }

                if (!next_subvol) {
                        goto unwind;
                }

                STACK_WIND (frame, dht_readdirp_cbk,
                            next_subvol, next_subvol->fops->readdirp,
                            local->fd, local->size, next_offset,
                            local->xattr);
                return 0;
        }

unwind:
        if (op_ret < 0)
                op_ret = 0;

        DHT_STACK_UNWIND (readdirp, frame, op_ret, op_errno, &entries, NULL);

        gf_dirent_free (&entries);

        return 0;
}
