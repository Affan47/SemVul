ifp_write_close(struct ifp_device * dev)
{
	int i = 0;
	int e = 0;
	int remainder = dev->current_offset % IFP_BULK_BUFF_SIZE;
	if (remainder != 0) {
		i = ifp_file_upload(dev, dev->iobuff, remainder);
		if (i) {
			ifp_err_i(i, "problem uploading last %d bytes.  "
			"Attempting to close file anyways.", remainder);
			e=e?e:i;

		}
	}

#if 0

	ifp_wrn_on(dev->current_offset != dev->filesize,
		"received %d fewer bytes than expected",
		(int)(dev->filesize - dev->current_offset));
#endif


	i = ifp_file_flush(dev);
	if (i) {
		ifp_err_i(i, "flush failed, closing anyways.");
		e=e?e:i;

	}

	i = ifp_file_close(dev);
	if (i) {
		ifp_err_i(i, "file close failed, closing dir anyways.");
		e=e?e:i;

	}
	i = ifp_dir_close(dev);
	if (i) {
		ifp_err_i(i, "dir close failed.");
		e=e?e:i;
	}

	if (e == 0) {
		i = quick_write_verify(dev);
		if (i) {
			ifp_err_i(i, "quick-verify failed--upload may have failed.");
		}
	}
	dev->mode = IFP_MODE_NONE;

	return i?i:e;
}
