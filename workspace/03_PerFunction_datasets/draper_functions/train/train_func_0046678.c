ifp_file_open(struct ifp_device * dev, const char * s)
{
	int i;

	i = _ifp_set_buffer_size(dev, IFP_PATH_XFER_SIZE, 1);
	ifp_err_jump(i, out, "set buffer failed");
	i = _ifp_push_unicode(dev, s, IFP_PATH_XFER_SIZE);
	ifp_err_jump(i, out, "push failed");
	i = _ifp_file_open(dev, IFP_FILE);
	if (i == 1) {
		i = -ENOENT;
	} else if (i != 0) {
		ifp_err_i(i, "open directive failed");
	}

out:
	return i;
}
