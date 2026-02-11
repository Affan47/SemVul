cryptdes(char *key)
{
	unsigned char salt[2];
	int fd = open("/dev/random", 2);
	if (fd == -1) {
		puts("Sorry, crypt not available: Cannot open /dev/random.");
		return 0;
	}
	if (read(fd, salt, 2) != 2) syserr();
	close(fd);
	salt[0] = saltbag[salt[0] & 63];
	salt[1] = saltbag[salt[1] & 63];
	return crypt(key, (char *) salt);
}
