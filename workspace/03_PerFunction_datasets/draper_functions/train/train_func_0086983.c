show_memory(struct device *d, struct device_attribute *attr,
			   char *buf)
{
	struct ipw2100_priv *priv = dev_get_drvdata(d);
	struct net_device *dev = priv->net_dev;
	static unsigned long loop = 0;
	int len = 0;
	u32 buffer[4];
	int i;
	char line[81];

	if (loop >= 0x30000)
		loop = 0;


	while (len < PAGE_SIZE - 128 && loop < 0x30000) {

		if (priv->snapshot[0])
			for (i = 0; i < 4; i++)
				buffer[i] =
				    *(u32 *) SNAPSHOT_ADDR(loop + i * 4);
		else
			for (i = 0; i < 4; i++)
				read_nic_dword(dev, loop + i * 4, &buffer[i]);

		if (priv->dump_raw)
			len += sprintf(buf + len,
				       "%c%c%c%c"
				       "%c%c%c%c"
				       "%c%c%c%c"
				       "%c%c%c%c",
				       ((u8 *) buffer)[0x0],
				       ((u8 *) buffer)[0x1],
				       ((u8 *) buffer)[0x2],
				       ((u8 *) buffer)[0x3],
				       ((u8 *) buffer)[0x4],
				       ((u8 *) buffer)[0x5],
				       ((u8 *) buffer)[0x6],
				       ((u8 *) buffer)[0x7],
				       ((u8 *) buffer)[0x8],
				       ((u8 *) buffer)[0x9],
				       ((u8 *) buffer)[0xa],
				       ((u8 *) buffer)[0xb],
				       ((u8 *) buffer)[0xc],
				       ((u8 *) buffer)[0xd],
				       ((u8 *) buffer)[0xe],
				       ((u8 *) buffer)[0xf]);
		else
			len += sprintf(buf + len, "%s\n",
				       snprint_line(line, sizeof(line),
						    (u8 *) buffer, 16, loop));
		loop += 16;
	}

	return len;
}
