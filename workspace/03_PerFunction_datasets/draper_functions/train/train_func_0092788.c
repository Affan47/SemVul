xgbe_vid_crc32_le(__le16 vid_le)
{
	u32 poly = CRCPOLY_LE;
	u32 crc = ~0;
	u32 temp = 0;
	unsigned char *data = (unsigned char *)&vid_le;
	unsigned char data_byte = 0;
	int i, bits;

	bits = get_bitmask_order(VLAN_VID_MASK);
	for (i = 0; i < bits; i++) {
		if ((i % 8) == 0)
			data_byte = data[i / 8];

		temp = ((crc & 1) ^ data_byte) & 1;
		crc >>= 1;
		data_byte >>= 1;

		if (temp)
			crc ^= poly;
	}

	return crc;
}
