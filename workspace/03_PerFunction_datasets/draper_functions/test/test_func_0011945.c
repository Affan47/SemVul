maGetUserGroup(MaAppweb *appweb)
{
#if BLD_UNIX_LIKE
    struct passwd   *pp;
    struct group    *gp;

    appweb->uid = getuid();
    if ((pp = getpwuid(appweb->uid)) == 0) {
        mprError("Can't read user credentials: %d. Check your /etc/passwd file.", appweb->uid);
    } else {
        appweb->user = sclone(pp->pw_name);
    }
    appweb->gid = getgid();
    if ((gp = getgrgid(appweb->gid)) == 0) {
        mprError("Can't read group credentials: %d. Check your /etc/group file", appweb->gid);
    } else {
        appweb->group = sclone(gp->gr_name);
    }
#else
    appweb->uid = appweb->gid = -1;
#endif
}
