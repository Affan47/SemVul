fuse_nameless_lookup (xlator_t *xl, uuid_t gfid, loc_t *loc)
{
        int          ret          = -1;
        dict_t      *xattr_req    = NULL;
        struct iatt  iatt         = {0, };

        if ((loc == NULL) || (xl == NULL)) {
                goto out;
        }

        if (loc->inode == NULL) {
                loc->inode = inode_new (xl->itable);
                if (loc->inode == NULL) {
                        goto out;
                }
        }

        uuid_copy (loc->gfid, gfid);

        xattr_req = dict_new ();
        if (xattr_req == NULL) {
                goto out;
        }

        ret = syncop_lookup (xl, loc, xattr_req, &iatt, NULL, NULL);
        if (ret < 0) {
                goto out;
        }

        inode_link (loc->inode, NULL, NULL, &iatt);

        ret = 0;
out:
        if (xattr_req != NULL) {
                dict_unref (xattr_req);
        }

        return ret;
}
