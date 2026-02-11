init_act2dev(struct act2_eegdev* a2dev, unsigned int nch)
{
 	int i;

	if (act2_open_dev(a2dev))
		return -1;


	for (i=0; i<NUMURB; i++) {
		if (!(a2dev->urb[i] = libusb_alloc_transfer(0))
		  ||!(a2dev->urb[i]->buffer=page_aligned_malloc(CHUNKSIZE)))
			goto error;

		libusb_fill_bulk_transfer(a2dev->urb[i],
		                          a2dev->hudev, ACT2_EP_IN,
		                          a2dev->urb[i]->buffer, CHUNKSIZE,
		                          req_completion_fn, a2dev,
		                          ACT2_TIMEOUT);
	}

	a2dev->optnch = nch;
	if (nch == 32)
		a2dev->eeglabel = eeg32label;
	else if (nch == 64)
		a2dev->eeglabel = eeg64label;
	else
		a2dev->eeglabel = eeg256label;
	return 0;

error:
	for (i=0; i<NUMURB; i++) {
		if (a2dev->urb[i]) {
			free(a2dev->urb[i]->buffer);
			libusb_free_transfer(a2dev->urb[i]);
		}
	}
	act2_close_dev(a2dev);
	return -1;
}
