libssh2_sftp_fstatvfs(LIBSSH2_SFTP_HANDLE *handle, LIBSSH2_SFTP_STATVFS *st)
{
    int rc;
    if(!handle || !st)
        return LIBSSH2_ERROR_BAD_USE;
    BLOCK_ADJUST(rc, handle->sftp->channel->session, sftp_fstatvfs(handle, st));
    return rc;
}
