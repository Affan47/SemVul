mei_cldev_recv(struct mei_cl_device *cldev, u8 *buf, size_t length)
{
	struct mei_cl *cl = cldev->cl;

	if (cl == NULL)
		return -ENODEV;

	return __mei_cl_recv(cl, buf, length);
}
