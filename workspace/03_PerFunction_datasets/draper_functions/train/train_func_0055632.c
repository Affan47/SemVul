_MD_SyncMemMap(
    PRFileDesc *fd,
    void *addr,
    PRUint32 len)
{


    if (msync(addr, len, MS_SYNC) == 0) {
        return PR_SUCCESS;
    }
    _PR_MD_MAP_DEFAULT_ERROR(errno);
    return PR_FAILURE;
}
