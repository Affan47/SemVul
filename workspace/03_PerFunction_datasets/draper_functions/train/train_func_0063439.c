dht_subvol_get_hashed (xlator_t *this, loc_t *loc)
{
        dht_layout_t *layout = NULL;
        xlator_t     *subvol = NULL;

        GF_VALIDATE_OR_GOTO ("dht", this, out);
        GF_VALIDATE_OR_GOTO (this->name, loc, out);

        if (__is_root_gfid (loc->gfid)) {
                subvol = dht_first_up_subvol (this);
                goto out;
        }

        GF_VALIDATE_OR_GOTO (this->name, loc->parent, out);
        GF_VALIDATE_OR_GOTO (this->name, loc->name, out);

        layout = dht_layout_get (this, loc->parent);

        if (!layout) {
                gf_log (this->name, GF_LOG_DEBUG,
                        "layout missing path=%s parent=%s",
                        loc->path, uuid_utoa (loc->parent->gfid));
                goto out;
        }

        subvol = dht_layout_search (this, layout, loc->name);

        if (!subvol) {
                gf_log (this->name, GF_LOG_DEBUG,
                        "could not find subvolume for path=%s",
                        loc->path);
                goto out;
        }

out:
        if (layout) {
                dht_layout_unref (this, layout);
        }

        return subvol;
}
