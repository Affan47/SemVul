full_write(int out_fd, const char * data, ft_size len, const char * target_path)
{
    ft_size chunk;
    int err = 0;
    while (len) {
        while ((chunk = ::write(out_fd, data, len)) == (ft_size)-1 && errno == EINTR)
            ;
        if (chunk == 0 || chunk == (ft_size)-1) {
            err = ff_log(FC_ERROR, errno, "error writing to `%s'", target_path);
            break;
        }
        data += chunk;
        len -= chunk;

        if ((err = this->periodic_check_free_space(chunk)) != 0)
            break;
    }
    return err;
}
