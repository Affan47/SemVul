slave_alloc (struct scsi_device *sdev)
{
	struct us_data *us = host_to_us(sdev->host);


	sdev->inquiry_len = 36;


	blk_queue_update_dma_alignment(sdev->request_queue, (512 - 1));


	if (us->protocol == USB_PR_BULK && us->max_lun > 0)
		sdev->sdev_bflags |= BLIST_FORCELUN;

	return 0;
}
