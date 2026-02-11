SMBus_block_process_call(SMBus *self, PyObject *args)
{
	int addr, cmd;
	union i2c_smbus_data data;

	if (!PyArg_ParseTuple(args, "iiO&:block_process_call", &addr, &cmd,
			SMBus_list_to_data, &data))
		return NULL;

	SMBus_SET_ADDR(self, addr);


	if (i2c_smbus_access(self->fd, I2C_SMBUS_WRITE, (__u8)cmd,
				I2C_SMBUS_BLOCK_PROC_CALL, &data)) {
		PyErr_SetFromErrno(PyExc_IOError);
		return NULL;
	}


	return SMBus_buf_to_list(&data.block[1], data.block[0]);
}
