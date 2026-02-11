oss_mixer_set(oss_mixer_t *self, PyObject *args)
{
    int channel, volume, leftVol, rightVol;

    if (!_is_fd_valid(self->fd))
        return NULL;


    if (!PyArg_ParseTuple(args, "i(ii):set", &channel, &leftVol, &rightVol))
        return NULL;

    if (channel < 0 || channel > SOUND_MIXER_NRDEVICES) {
        PyErr_SetString(OSSAudioError, "Invalid mixer channel specified.");
        return NULL;
    }

    if (leftVol < 0 || rightVol < 0 || leftVol > 100 || rightVol > 100) {
        PyErr_SetString(OSSAudioError, "Volumes must be between 0 and 100.");
        return NULL;
    }

    volume = (rightVol << 8) | leftVol;

    if (ioctl(self->fd, MIXER_WRITE(channel), &volume) == -1)
        return PyErr_SetFromErrno(PyExc_IOError);

    return Py_BuildValue("(ii)", volume & 0xff, (volume & 0xff00) >> 8);
}
