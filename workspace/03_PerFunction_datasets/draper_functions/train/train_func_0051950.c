ExpandTempFile( string &dataT, bool unlockT )
{
    int total_written = 0;
    int len = dataT.length();
    int ret;

    TempFileLength += len;


    while (total_written < len)
    {
        while ((ret = write(fd_tempfile, dataT.substr(total_written).c_str(), len - total_written)) < 0)
        {
            if (errno == EINTR) continue;

            LogFile::ErrorMessage("Could not expand tempfile: %s %s\n", TempFileName, strerror(errno));
            return false;
        }

        total_written += ret;
    }

#ifndef NOMAND

    if (unlockT == true)
    {
        struct flock lock;

        lock.l_type   = F_UNLCK;
        lock.l_start  = 0;
        lock.l_whence = SEEK_SET;
        lock.l_len    = TempFileLength;

        while (fcntl(fd_tempfile, F_SETLK, &lock) < 0)
        {
            if (errno == EINTR) continue;

            LogFile::ErrorMessage("Could not unlock file: %s\n", TempFileName);
            return false;
        }
    }
#endif

    return true;
}
