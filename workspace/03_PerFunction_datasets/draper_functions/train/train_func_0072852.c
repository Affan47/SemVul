av_fd_read(int fd, void *buf, avsize_t nbyte)
{
    avssize_t res;
    vfile *vf;

    res = get_file(fd, &vf);
    if(res == 0) {
        res = av_file_read(vf, buf, nbyte);
        put_file(vf);
    }

    return res;
}
