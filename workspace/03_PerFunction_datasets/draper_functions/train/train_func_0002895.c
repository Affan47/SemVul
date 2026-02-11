set_unit_directory(quadlet_t *buffer, rom1394_directory *dir)
{
	int i, length;
	quadlet_t *p = buffer;
	int	key, value;
	quadlet_t quadlet;

	quadlet = ntohl(*p);
	length = quadlet >> 16;

	DEBUG(-1, "directory has %d entries\n", length);
	for (i=0; i < length; i++) {
		p++;
		quadlet = ntohl(*p);
		key = quadlet >> 24;
   		value = quadlet & 0x00FFFFFF;
		DEBUG(-1, "key/value: %08x/%08x\n", key, value);

		switch (key) {
			case 0x12:
				if (dir->unit_spec_id != -1)
				{
					value = (key << 24) | (dir->unit_spec_id & 0x00FFFFFF);
					*p = htonl(value);
				}
				break;
			case 0x13:
				if (dir->unit_sw_version != -1)
				{
					value = (key << 24) | (dir->unit_sw_version & 0x00FFFFFF);
					*p = htonl(value);
				}
				break;
			case 0x81:
			case 0x82:


				break;
		}
	}


	p = buffer;
	quadlet = (length << 16);
	quadlet |= make_crc(p + 1, length) & 0x0000FFFF;
	*p = htonl(quadlet);

	return 0;
}
