passfd_recvfd(PyObject *self, PyObject *args)
{
	int sockfd, fd;

	if (!PyArg_ParseTuple(args, "i:recvfd", &sockfd))
		return NULL;

	if ((fd = recv_fd(sockfd)) < 0) {
		PyErr_SetFromErrno(PyExc_IOError);
		return NULL;
	}

	return PyInt_FromLong((long) fd);
}
