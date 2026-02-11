map_file(void)
{
#ifndef __MINGW32__
    size_t size = HEADER_SIZE + width * height * sizeof(unsigned int);
    void *ptr;
    int fd;

    fd = open(file_name, O_RDWR);
    if (fd < 0)
	return;

    ptr = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, (off_t) 0);
    if (ptr == MAP_FAILED)
	return;

    if (grid) {
	cairo_destroy(cairo);
	cairo_surface_destroy(surface);
	G_free(grid);
    }
    grid = (unsigned char *)ptr + HEADER_SIZE;

    close(fd);

    mapped = 1;
#endif
}
