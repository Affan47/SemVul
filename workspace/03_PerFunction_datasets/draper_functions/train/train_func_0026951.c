open_write(const char *fname, os_filetype_t typ)
{

    fp_ = osfopwb(fname, typ);


    if (fp_ == 0)
        err_throw(VMERR_CREATE_FILE);
}
