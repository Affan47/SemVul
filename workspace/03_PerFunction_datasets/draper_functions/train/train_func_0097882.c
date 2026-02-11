i2c_read_bytes(const int fd, uint8_t *buffer, int size) throw(const char *) {
	if (read(fd, buffer, size) != size) {
		throw "i2c: Failed to read to slave!";
	}
}
