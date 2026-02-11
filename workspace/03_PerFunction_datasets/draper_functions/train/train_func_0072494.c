oss_post(oss_audio_t *self, PyObject *args)
{
    if (!_is_fd_valid(self->fd))
        return NULL;

    return _do_ioctl_0(self->fd, args, "post", SNDCTL_DSP_POST);
}
