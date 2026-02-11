fuse_forget (xlator_t *this, fuse_in_header_t *finh, void *msg)

{
        struct fuse_forget_in *ffi = msg;

        inode_t      *fuse_inode;

        if (finh->nodeid == 1) {
                GF_FREE (finh);
                return;
        }

        gf_log ("glusterfs-fuse", GF_LOG_TRACE,
                "%"PRIu64": FORGET %"PRIu64"/%"PRIu64,
                finh->unique, finh->nodeid, ffi->nlookup);

        fuse_inode = fuse_ino_to_inode (finh->nodeid, this);

        inode_forget (fuse_inode, ffi->nlookup);
        inode_unref (fuse_inode);

        GF_FREE (finh);
}
