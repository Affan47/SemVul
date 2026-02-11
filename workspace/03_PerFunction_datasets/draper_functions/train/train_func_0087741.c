afr_crawl_build_start_loc (xlator_t *this, afr_crawl_data_t *crawl_data,
                           loc_t *dirloc)
{
        afr_private_t *priv = NULL;
        dict_t        *xattr = NULL;
        void          *index_gfid = NULL;
        loc_t         rootloc = {0};
        struct iatt   iattr = {0};
        struct iatt   parent = {0};
        int           ret = 0;
        xlator_t      *readdir_xl = crawl_data->readdir_xl;

        priv = this->private;
        if (crawl_data->crawl == FULL) {
                afr_build_root_loc (this, dirloc);
        } else {
                afr_build_root_loc (this, &rootloc);
                ret = syncop_getxattr (readdir_xl, &rootloc, &xattr,
                                       GF_XATTROP_INDEX_GFID);
                if (ret < 0)
                        goto out;
                ret = dict_get_ptr (xattr, GF_XATTROP_INDEX_GFID, &index_gfid);
                if (ret < 0) {
                        gf_log (this->name, GF_LOG_ERROR, "failed to get index "
                                "dir gfid on %s", readdir_xl->name);
                        goto out;
                }
                if (!index_gfid) {
                        gf_log (this->name, GF_LOG_ERROR, "index gfid empty "
                                "on %s", readdir_xl->name);
                        ret = -1;
                        goto out;
                }
                uuid_copy (dirloc->gfid, index_gfid);
                dirloc->path = "";
                dirloc->inode = inode_new (priv->root_inode->table);
                ret = syncop_lookup (readdir_xl, dirloc, NULL,
                                     &iattr, NULL, &parent);
                if (ret < 0) {
                        if (errno != ENOENT) {
                                gf_log (this->name, GF_LOG_ERROR, "lookup "
                                        "failed on index dir on %s - (%s)",
                                        readdir_xl->name, strerror (errno));
                        }
                        goto out;
                }
                ret = _link_inode_update_loc (this, dirloc, &iattr);
                if (ret)
                        goto out;
        }
        ret = 0;
out:
        if (xattr)
                dict_unref (xattr);
        loc_wipe (&rootloc);
        return ret;
}
