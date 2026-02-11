posix_do_fchown (xlator_t *this,
                 int fd,
                 struct iatt *stbuf,
                 int32_t valid)
{
        int   ret      = -1;
        uid_t uid = -1;
        gid_t gid = -1;

        if (valid & GF_SET_ATTR_UID)
                uid = stbuf->ia_uid;

        if (valid & GF_SET_ATTR_GID)
                gid = stbuf->ia_gid;

        ret = fchown (fd, uid, gid);

        return ret;
}
