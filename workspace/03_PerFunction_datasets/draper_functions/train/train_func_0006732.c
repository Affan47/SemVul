usb_stor_bulk_transfer_sg(struct us_data* us, unsigned int pipe,
		void *buf, unsigned int length_left, int use_sg, int *residual)
{
	int result;
	unsigned int partial;


	if (use_sg) {

		result = usb_stor_bulk_transfer_sglist(us, pipe,
				(struct scatterlist *) buf, use_sg,
				length_left, &partial);
		length_left -= partial;
	} else {

		result = usb_stor_bulk_transfer_buf(us, pipe, buf,
				length_left, &partial);
		length_left -= partial;
	}


	if (residual)
		*residual = length_left;
	return result;
}
