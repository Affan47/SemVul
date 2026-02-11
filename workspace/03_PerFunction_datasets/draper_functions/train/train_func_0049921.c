ucode_regs_read_file(struct b43legacy_wldev *dev, char *buf, size_t bufsize)
{
	ssize_t count = 0;
	int i;

	for (i = 0; i < 64; i++) {
		fappend("r%d = 0x%04x\n", i,
			b43legacy_shm_read16(dev, B43legacy_SHM_WIRELESS, i));
	}

	return count;
}
