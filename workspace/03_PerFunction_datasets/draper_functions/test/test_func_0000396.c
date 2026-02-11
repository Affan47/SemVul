buf_same_ino(buf, stp)
    buf_T	*buf;
    struct stat *stp;
{
    return (buf->b_dev >= 0
	    && stp->st_dev == buf->b_dev
	    && stp->st_ino == buf->b_ino);
}
