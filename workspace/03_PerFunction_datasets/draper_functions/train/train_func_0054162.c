trim_sectors (int fd, const char *devname, int nranges, void *data, __u64 nsectors)
{
	struct ata_tf tf;
	int err = 0;
	unsigned int data_bytes = nranges * sizeof(__u64);
	unsigned int data_sects = (data_bytes + 511) / 512;

	data_bytes = data_sects * 512;

	abort_if_not_full_device(fd, 0, devname, NULL);
	printf("trimming %llu sectors from %d ranges\n", nsectors, nranges);
	fflush(stdout);


	flush_buffer_cache(fd);

	tf_init(&tf, ATA_OP_DSM, 0, data_sects);
	tf.lob.feat = 0x01;

	if (sg16(fd, SG_WRITE, SG_DMA, &tf, data, data_bytes, 300 )) {
		err = errno;
		perror("FAILED");
	} else {
		printf("succeeded\n");
	}
	return err;
}
