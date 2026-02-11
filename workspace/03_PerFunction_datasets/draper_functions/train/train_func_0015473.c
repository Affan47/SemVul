pm_parse_6250(struct pm *pm)
{
	struct input_dev *dev = pm->dev;

	if ((pm->data[0] & 0xb0) == 0x30 && pm->packetsize == ++pm->idx) {
		if (pm_checkpacket(pm->data)) {
			int slotnum = pm->data[0] & 0x0f;
			pm->slots[slotnum].active = pm->data[0] & 0x40;
			pm->slots[slotnum].x = pm->data[2] * 256 + pm->data[1];
			pm->slots[slotnum].y = pm->data[4] * 256 + pm->data[3];
			pm_mtevent(pm, dev);
		}
		pm->idx = 0;
	}
}
