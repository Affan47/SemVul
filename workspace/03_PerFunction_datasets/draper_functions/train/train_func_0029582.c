create_bo(int fd, uint32_t val)
{
	uint32_t handle;
	int i;

	handle = gem_create(fd, sizeof(linear));


	for (i = 0; i < WIDTH*HEIGHT; i++)
		linear[i] = val++;
	gem_write(fd, handle, 0, linear, sizeof(linear));

	return handle;
}
