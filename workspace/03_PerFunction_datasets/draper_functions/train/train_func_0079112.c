virt_fchown(int fd, uid_t owner, gid_t grp)
{
    struct avstat stbuf;
    int attrmask = 0;

    stbuf.uid = owner;
    stbuf.gid = grp;

    if(owner != (uid_t) -1)
	attrmask |= AVA_UID;
    if(grp != (gid_t) -1)
	attrmask |= AVA_GID;

    return common_fsetattr(fd, &stbuf, attrmask);
}
