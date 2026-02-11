create_bo(int fd)
{
	uint32_t handle;
	uint32_t *data;
	int i;

	handle = gem_create(fd, OBJ_SIZE);


	data = gem_mmap(fd, handle, OBJ_SIZE, PROT_READ | PROT_WRITE);
	for (i = 0; i < OBJ_SIZE/4; i++)
		data[i] = i;
	munmap(data, OBJ_SIZE);

	return handle;
}
