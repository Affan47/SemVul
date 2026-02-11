print_size(unsigned long size)
{
	static char	unit[] = "-kMG";
	static char	buffer[64];
	unsigned int	power = 0;

	while (size && !(size % 1024) && power < sizeof(unit)) {
		size /= 1024;
		power++;
	}

	if (!power) {
		snprintf(buffer, sizeof(buffer), "%lu", size);
	} else {
		snprintf(buffer, sizeof(buffer), "%lu%c",
				size, unit[power]);
	}
	return buffer;
}
