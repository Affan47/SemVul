mmio32write__write_file(struct b43_wldev *dev,
				   const char *buf, size_t count)
{
	unsigned int addr, mask, set;
	int res;
	u32 val;

	res = sscanf(buf, "0x%X 0x%X 0x%X", &addr, &mask, &set);
	if (res != 3)
		return -EINVAL;
	if (addr > B43_MAX_MMIO_ACCESS)
		return -EADDRNOTAVAIL;
	if ((mask > 0xFFFFFFFF) || (set > 0xFFFFFFFF))
		return -E2BIG;
	if ((addr % 4) != 0)
		return -EINVAL;

	if (mask == 0)
		val = 0;
	else
		val = b43_read32(dev, addr);
	val &= mask;
	val |= set;
	b43_write32(dev, addr, val);

	return 0;
}
