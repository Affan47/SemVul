nilfs_segbuf_wait(struct nilfs_segment_buffer *segbuf)
{
	int err = 0;

	if (!segbuf->sb_nbio)
		return 0;

	do {
		wait_for_completion(&segbuf->sb_bio_event);
	} while (--segbuf->sb_nbio > 0);

	if (unlikely(atomic_read(&segbuf->sb_err) > 0)) {
		printk(KERN_ERR "NILFS: IO error writing segment\n");
		err = -EIO;
	}
	return err;
}
