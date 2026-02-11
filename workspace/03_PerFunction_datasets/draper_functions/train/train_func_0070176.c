write_thread(file_descriptor *pfd)
{
	int ep = -1;

	pthread_detach(pthread_self());

	ep = get_out_ep(libusb_dev, pfd->config, pfd->interface, pfd->alt_setting, LIBUSB_TRANSFER_TYPE_BULK);
	if (ep < 0)
	{
		BUG("invalid bulk out endpoint\n");
		goto bugout;
	}


	pfd->write_return = libusb_bulk_write (pfd->hd, ep, (char *)pfd->write_buf, pfd->write_size, 72*3600*1000);

bugout:
	pthread_mutex_lock(&pfd->mutex);
	pfd->write_buf = NULL;
	pthread_cond_signal(&pfd->write_done_cond);
	pthread_mutex_unlock(&pfd->mutex);

	return;
}
