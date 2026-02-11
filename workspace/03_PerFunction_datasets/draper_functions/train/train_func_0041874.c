SMBus_write_block_data(SMBus *self, PyObject *args)
{
	int addr, cmd;
	union i2c_smbus_data data;

	if (!PyArg_ParseTuple(args, "iiO&:write_block_data", &addr, &cmd,
				SMBus_list_to_data, &data))
		return NULL;

	SMBus_SET_ADDR(self, addr);


	if (i2c_smbus_access(self->fd, I2C_SMBUS_WRITE, (__u8)cmd,
				I2C_SMBUS_BLOCK_DATA, &data)) {
		PyErr_SetFromErrno(PyExc_IOError);
		return NULL;
	}

	Py_INCREF(Py_None);
	return Py_None;
}
