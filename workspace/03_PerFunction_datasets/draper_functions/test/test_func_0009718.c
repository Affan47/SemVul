SMBus_close(SMBus *self)
{
	if ((self->fd != -1) && (close(self->fd) == -1)) {
		PyErr_SetFromErrno(PyExc_IOError);
		return NULL;
	}

	self->fd = -1;
	self->addr = -1;
	self->pec = 0;

	Py_INCREF(Py_None);
	return Py_None;
}
