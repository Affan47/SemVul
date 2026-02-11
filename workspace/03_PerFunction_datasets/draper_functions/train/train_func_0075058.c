end_workqueue_bio(struct bio *bio)
{
	struct btrfs_end_io_wq *end_io_wq = bio->bi_private;
	struct btrfs_fs_info *fs_info;
	struct btrfs_workqueue *wq;
	btrfs_work_func_t func;

	fs_info = end_io_wq->info;
	end_io_wq->error = bio->bi_error;

	if (bio->bi_rw & REQ_WRITE) {
		if (end_io_wq->metadata == BTRFS_WQ_ENDIO_METADATA) {
			wq = fs_info->endio_meta_write_workers;
			func = btrfs_endio_meta_write_helper;
		} else if (end_io_wq->metadata == BTRFS_WQ_ENDIO_FREE_SPACE) {
			wq = fs_info->endio_freespace_worker;
			func = btrfs_freespace_write_helper;
		} else if (end_io_wq->metadata == BTRFS_WQ_ENDIO_RAID56) {
			wq = fs_info->endio_raid56_workers;
			func = btrfs_endio_raid56_helper;
		} else {
			wq = fs_info->endio_write_workers;
			func = btrfs_endio_write_helper;
		}
	} else {
		if (unlikely(end_io_wq->metadata ==
			     BTRFS_WQ_ENDIO_DIO_REPAIR)) {
			wq = fs_info->endio_repair_workers;
			func = btrfs_endio_repair_helper;
		} else if (end_io_wq->metadata == BTRFS_WQ_ENDIO_RAID56) {
			wq = fs_info->endio_raid56_workers;
			func = btrfs_endio_raid56_helper;
		} else if (end_io_wq->metadata) {
			wq = fs_info->endio_meta_workers;
			func = btrfs_endio_meta_helper;
		} else {
			wq = fs_info->endio_workers;
			func = btrfs_endio_helper;
		}
	}

	btrfs_init_work(&end_io_wq->work, func, end_workqueue_fn, NULL, NULL);
	btrfs_queue_work(wq, &end_io_wq->work);
}
