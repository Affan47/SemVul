quota_loc_fill (loc_t *loc, inode_t *inode, inode_t *parent, char *path)
{
        int ret = -1;

        if (!loc) {
                return ret;
        }

        if (inode) {
                loc->inode = inode_ref (inode);
        }

        if (parent) {
                loc->parent = inode_ref (parent);
        }

        loc->path = gf_strdup (path);
        if (!loc->path) {
                goto loc_wipe;
        }

        loc->name = strrchr (loc->path, '/');
        if (loc->name) {
                loc->name++;
        } else {
                goto loc_wipe;
        }

        ret = 0;

loc_wipe:
        if (ret < 0) {
                loc_wipe (loc);
        }

        return ret;
}
