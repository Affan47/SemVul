oss_obuffree(oss_audio_t *self, PyObject *unused)
{
    audio_buf_info ai;
    int nchannels=0, ssize=0;

    if (!_is_fd_valid(self->fd))
        return NULL;

    if (_ssize(self, &nchannels, &ssize) < 0 || !nchannels || !ssize) {
        PyErr_SetFromErrno(PyExc_IOError);
        return NULL;
    }
    if (ioctl(self->fd, SNDCTL_DSP_GETOSPACE, &ai) < 0) {
        PyErr_SetFromErrno(PyExc_IOError);
        return NULL;
    }
    return PyLong_FromLong(ai.bytes / (ssize * nchannels));
}
