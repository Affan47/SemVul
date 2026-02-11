fuse_ino_to_inode (uint64_t ino, xlator_t *fuse)
{
        inode_t  *inode = NULL;
        xlator_t *active_subvol = NULL;

        if (ino == 1) {
                active_subvol = fuse_active_subvol (fuse);
                if (active_subvol)
                        inode = active_subvol->itable->root;
        } else {
                inode = (inode_t *) (unsigned long) ino;
                inode_ref (inode);
        }

        return inode;
}
