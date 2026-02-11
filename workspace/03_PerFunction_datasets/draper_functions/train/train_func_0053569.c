afr_prepare_loc (call_frame_t *frame, fd_t *fd)
{
        afr_local_t    *local = NULL;
        char           *name = NULL;
        char           *path = NULL;
        int             ret = 0;

        if ((!fd) || (!fd->inode))
                return -1;

        local = frame->local;
        ret = inode_path (fd->inode, NULL, (char **)&path);
        if (ret <= 0) {
                gf_log (frame->this->name, GF_LOG_DEBUG,
                        "Unable to get path for gfid: %s",
                        uuid_utoa (fd->inode->gfid));
                return -1;
        }

        if (local->loc.path) {
                if (strcmp (path, local->loc.path))
                        gf_log (frame->this->name, GF_LOG_DEBUG,
                                "overwriting old loc->path %s with %s",
                                local->loc.path, path);
                GF_FREE ((char *)local->loc.path);
        }
        local->loc.path = path;

        name = strrchr (local->loc.path, '/');
        if (name)
                name++;
        local->loc.name = name;

        if (local->loc.inode) {
                inode_unref (local->loc.inode);
        }
        local->loc.inode = inode_ref (fd->inode);

        if (local->loc.parent) {
                inode_unref (local->loc.parent);
        }

        local->loc.parent = inode_parent (local->loc.inode, 0, NULL);

        return 0;
}
