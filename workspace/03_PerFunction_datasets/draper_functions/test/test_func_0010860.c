SMBus_read_byte_data(SMBus *self, PyObject *args)
{
	int addr, cmd;
	__s32 result;

	if (!PyArg_ParseTuple(args, "ii:read_byte_data", &addr, &cmd))
		return NULL;

	SMBus_SET_ADDR(self, addr);

	if ((result = i2c_smbus_read_byte_data(self->fd, (__u8)cmd)) == -1) {
		PyErr_SetFromErrno(PyExc_IOError);
		return NULL;
	}

	return Py_BuildValue("l", (long)result);
}
