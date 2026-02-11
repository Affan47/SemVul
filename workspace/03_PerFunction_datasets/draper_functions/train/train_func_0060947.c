afr_is_new_entry_changelog_needed (glusterfs_fop_t fop)
{
        glusterfs_fop_t fops[]   = {GF_FOP_CREATE, GF_FOP_MKNOD, GF_FOP_NULL};
        int             i        = 0;

        for (i = 0; fops[i] != GF_FOP_NULL; i++) {
                if (fop == fops[i])
                        return _gf_true;
        }
        return _gf_false;
}
