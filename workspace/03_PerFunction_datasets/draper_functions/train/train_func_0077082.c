read_off(int fd)
{
	uint64_t buffer;
	if(read(fd,&buffer,8)<8)
		return 0;
	return be64_to_cpu(buffer);
}
