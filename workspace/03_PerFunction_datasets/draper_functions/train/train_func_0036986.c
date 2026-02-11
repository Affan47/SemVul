read_dev_mcast(struct ma_info **result_p)
{
	char buf[256];
	FILE *fp = fopen("/proc/net/dev_mcast", "r");

	if (!fp)
		return;

	while (fgets(buf, sizeof(buf), fp)) {
		char hexa[256];
		struct ma_info m;
		int len;
		int st;

		memset(&m, 0, sizeof(m));
		sscanf(buf, "%d%s%d%d%s", &m.index, m.name, &m.users, &st,
		       hexa);
		if (filter.dev && strcmp(filter.dev, m.name))
			continue;

		m.addr.family = AF_PACKET;

		len = parse_hex(hexa, (unsigned char*)&m.addr.data, sizeof (m.addr.data));
		if (len >= 0) {
			struct ma_info *ma = malloc(sizeof(m));

			memcpy(ma, &m, sizeof(m));
			ma->addr.bytelen = len;
			ma->addr.bitlen = len<<3;
			if (st)
				ma->features = "static";
			maddr_ins(result_p, ma);
		}
	}
	fclose(fp);
}
