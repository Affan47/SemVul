write_firmware_file(const char* filename, struct firmware *f) {
	int fd;
	unsigned char* data;
	off_t size = 0;

	fd = open(filename, O_WRONLY | O_CREAT, 0644);
	if(fd < 0) {
		perror("Error while opening the firmware file");
		return;
	}

	if(ftruncate(fd, 0) < 0) {
		perror("Error while deleting the firmware file");
		close(fd);
		return;
	}

	write_firmware(f, &data, &size);

	if(write(fd, data, size) < 0) {
		perror("Error while writing the firmware file");
		close(fd);
		return;
	}

	free(data);
	close(fd);
}
