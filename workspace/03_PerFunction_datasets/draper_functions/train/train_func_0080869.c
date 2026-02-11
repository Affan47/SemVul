pl_dump_inode_priv (xlator_t *this, inode_t *inode)
{

        int             ret = -1;
        uint64_t        tmp_pl_inode = 0;
        pl_inode_t      *pl_inode = NULL;

        int count      = 0;

        GF_VALIDATE_OR_GOTO (this->name, inode, out);

        ret = inode_ctx_get (inode, this, &tmp_pl_inode);

        if (ret != 0)
                goto out;

        pl_inode = (pl_inode_t *)(long)tmp_pl_inode;

        if (!pl_inode) {
                ret = -1;
                goto out;
        }

        gf_proc_dump_add_section("xlator.features.locks.%s.inode", this->name);

        gf_proc_dump_write("mandatory", "%d", pl_inode->mandatory);

        count = get_entrylk_count (this, inode);
        if (count) {
                gf_proc_dump_write("entrylk-count", "%d", count);
                dump_entrylks(pl_inode);
        }

        count = get_inodelk_count (this, inode);
        if (count) {
                gf_proc_dump_write("inodlk-count", "%d", count);
                dump_inodelks(pl_inode);
        }

        count = get_posixlk_count (this, inode);
        if (count) {
                gf_proc_dump_write("posixlk-count", "%d", count);
                dump_posixlks(pl_inode);
        }

out:
        return ret;
}
