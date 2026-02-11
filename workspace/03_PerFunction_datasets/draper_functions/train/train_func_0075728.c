carm_free_disks(struct carm_host *host)
{
	unsigned int i;

	for (i = 0; i < CARM_MAX_PORTS; i++) {
		struct gendisk *disk = host->port[i].disk;
		if (disk) {
			struct request_queue *q = disk->queue;

			if (disk->flags & GENHD_FL_UP)
				del_gendisk(disk);
			if (q)
				blk_cleanup_queue(q);
			put_disk(disk);
		}
	}
}
