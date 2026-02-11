next(fm_io_posix_dirent * & result)
{
    int err;
    if (this_dir == NULL)
        err = ENOTCONN;
    else {
        errno = 0;
        result = readdir(this_dir);
        if ((err = errno) == 0)
            return err;
    }
    err = ff_log(FC_ERROR, err, "failed to read directory `%s'", this_path.c_str());
    return err;
}
