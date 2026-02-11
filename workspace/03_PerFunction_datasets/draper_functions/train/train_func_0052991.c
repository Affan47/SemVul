dht_layout_merge (xlator_t *this, dht_layout_t *layout, xlator_t *subvol,
                  int op_ret, int op_errno, dict_t *xattr)
{
        int      i     = 0;
        int      ret   = -1;
        int      err   = -1;
        void    *disk_layout_raw = NULL;
        int      disk_layout_len = 0;

        if (op_ret != 0) {
                err = op_errno;
        }

        for (i = 0; i < layout->cnt; i++) {
                if (layout->list[i].xlator == NULL) {
                        layout->list[i].err    = err;
                        layout->list[i].xlator = subvol;
                        break;
                }
        }

        if (op_ret != 0) {
                ret = 0;
                goto out;
        }

        if (xattr) {

                ret = dict_get_ptr_and_len (xattr, "trusted.glusterfs.dht",
					    &disk_layout_raw, &disk_layout_len);
        }

        if (ret != 0) {
                layout->list[i].err = -1;
                gf_log (this->name, GF_LOG_TRACE,
                        "missing disk layout on %s. err = %d",
                        subvol->name, err);
                ret = 0;
                goto out;
        }

        ret = dht_disk_layout_merge (this, layout, i, disk_layout_raw,
				     disk_layout_len);
        if (ret != 0) {
                gf_log (this->name, GF_LOG_DEBUG,
                        "layout merge from subvolume %s failed",
                        subvol->name);
                goto out;
        }
        layout->list[i].err = 0;

out:
        return ret;
}
