gpt_write_header(struct fdisk_context *cxt,
			    struct gpt_header *header, uint64_t lba)
{
	off_t offset = lba * cxt->sector_size;

	if (offset != lseek(cxt->dev_fd, offset, SEEK_SET))
		goto fail;
	if (cxt->sector_size ==
	    (size_t) write(cxt->dev_fd, header, cxt->sector_size))
		return 0;
fail:
	return -errno;
}
