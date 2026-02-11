rom1394_get_size(quadlet_t *buffer)
{
	int i, length;
	quadlet_t *p = buffer + ROM1394_ROOT_DIRECTORY/4;
	int	key, value;
	quadlet_t quadlet;
	int x = ROM1394_ROOT_DIRECTORY/4 + 1;

	quadlet = ntohl(*p);
	length = quadlet >> 16;
	x += length;

	DEBUG(-1, "directory has %d entries\n", length);
	for (i=0; i < length; i++) {
		p++;
		quadlet = ntohl(*p);
		key = quadlet >> 24;
   		value = quadlet & 0x00FFFFFF;
		DEBUG(-1, "key/value: %08x/%08x\n", key, value);

		switch (key) {
   			case 0xD1:
				if (value > 0)
					x += get_unit_size(p + value);
				break;
			case 0x81:
				if (value > 0)
					x += get_leaf_size(p + value);
				break;
		}
	}

	return x;
}
