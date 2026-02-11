posix_gfid_set (xlator_t *this, const char *path, dict_t *xattr_req)
{
        void        *uuid_req = NULL;
        uuid_t       uuid_curr;
        int          ret = 0;
        struct stat  stat = {0, };

        if (!xattr_req)
                goto out;

        if (sys_lstat (path, &stat) != 0)
                goto out;

        ret = sys_lgetxattr (path, GFID_XATTR_KEY, uuid_curr, 16);
        if (ret == 16) {
                ret = 0;
                goto out;
        }

        ret = dict_get_ptr (xattr_req, "gfid-req", &uuid_req);
        if (ret) {
                gf_log_callingfn (this->name, GF_LOG_DEBUG,
                                  "failed to get the gfid from dict");
                goto out;
        }

        ret = sys_lsetxattr (path, GFID_XATTR_KEY, uuid_req, 16, XATTR_CREATE);

out:
        return ret;
}
