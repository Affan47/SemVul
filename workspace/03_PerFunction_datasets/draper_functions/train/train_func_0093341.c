pt_Available_s(PRFileDesc *fd)
{
    PRInt32 rv, bytes = -1;
    if (pt_TestAbort()) return bytes;

    rv = ioctl(fd->secret->md.osfd, FIONREAD, &bytes);

    if (rv == -1)
        pt_MapError(_PR_MD_MAP_SOCKETAVAILABLE_ERROR, errno);
    return bytes;
}
