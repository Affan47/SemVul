imm_biosparam(struct scsi_device *sdev, struct block_device *dev,
			 sector_t capacity, int ip[])
{
	ip[0] = 0x40;
	ip[1] = 0x20;
	ip[2] = ((unsigned long) capacity + 1) / (ip[0] * ip[1]);
	if (ip[2] > 1024) {
		ip[0] = 0xff;
		ip[1] = 0x3f;
		ip[2] = ((unsigned long) capacity + 1) / (ip[0] * ip[1]);
	}
	return 0;
}
