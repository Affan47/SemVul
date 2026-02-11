cfg_partition_read_block(int fd, void *buf, int blk, int blk_size)
{
	int	ret;

	ret = lseek(fd, blk * blk_size, SEEK_SET);
	if(ret != blk * blk_size) {
		printf("lseek: %08x, wanted: %08x, errno: %d\n", ret,
			blk * blk_size, errno);
		return 0;
	}

	ret = read(fd, (char *)buf, blk_size);
	if(ret != blk_size) {
		printf("ret: %08x, wanted %08x, errno: %d\n", ret, blk_size,
			errno);
		return 0;
	}
	return ret;
}
