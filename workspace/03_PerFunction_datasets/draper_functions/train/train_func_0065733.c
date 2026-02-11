ata_scsi_dev_config(struct scsi_device *sdev,
			       struct ata_device *dev)
{
	struct request_queue *q = sdev->request_queue;

	if (!ata_id_has_unload(dev->id))
		dev->flags |= ATA_DFLAG_NO_UNLOAD;


	blk_queue_max_hw_sectors(q, dev->max_sectors);

	if (dev->class == ATA_DEV_ATAPI) {
		void *buf;

		sdev->sector_size = ATA_SECT_SIZE;


		blk_queue_update_dma_pad(q, ATA_DMA_PAD_SZ - 1);


		buf = kmalloc(ATAPI_MAX_DRAIN, q->bounce_gfp | GFP_KERNEL);
		if (!buf) {
			ata_dev_err(dev, "drain buffer allocation failed\n");
			return -ENOMEM;
		}

		blk_queue_dma_drain(q, atapi_drain_needed, buf, ATAPI_MAX_DRAIN);
	} else {
		sdev->sector_size = ata_id_logical_sector_size(dev->id);
		sdev->manage_start_stop = 1;
	}


	if (sdev->sector_size > PAGE_SIZE)
		ata_dev_warn(dev,
			"sector_size=%u > PAGE_SIZE, PIO may malfunction\n",
			sdev->sector_size);

	blk_queue_update_dma_alignment(q, sdev->sector_size - 1);

	if (dev->flags & ATA_DFLAG_AN)
		set_bit(SDEV_EVT_MEDIA_CHANGE, sdev->supported_events);

	if (dev->flags & ATA_DFLAG_NCQ) {
		int depth;

		depth = min(sdev->host->can_queue, ata_id_queue_depth(dev->id));
		depth = min(ATA_MAX_QUEUE - 1, depth);
		scsi_change_queue_depth(sdev, depth);
	}

	blk_queue_flush_queueable(q, false);

	dev->sdev = sdev;
	return 0;
}
