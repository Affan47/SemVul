pl_lockinfo_get_brickname (xlator_t *this, inode_t *inode, int32_t *op_errno)
{
        int                    ret       = -1;
        posix_locks_private_t *priv      = NULL;
        char                  *brickname = NULL;
        char                  *end       = NULL;
        char                  *tmp       = NULL;

        priv = this->private;

        ret = fetch_pathinfo (this, inode, op_errno, &brickname);
        if (ret)
                goto out;

        end = strrchr (brickname, ':');
        if (!end) {
                GF_FREE(brickname);
                ret = -1;
                goto out;
        }

        tmp = brickname;
        brickname = gf_strndup (brickname, (end - brickname));
        if (brickname == NULL) {
                ret = -1;
                goto out;
        }

        priv->brickname = brickname;
        ret = 0;
out:
        GF_FREE(tmp);
        return ret;
}
