drop_privs(uid_t uid, gid_t gid)
{
    if (setgid(gid) < 0)
        return (-1);
    if (setuid(uid) < 0)
        return (-1);
    if (getgid() != gid || getuid() != uid)
        return (-1);
    return (0);
}
