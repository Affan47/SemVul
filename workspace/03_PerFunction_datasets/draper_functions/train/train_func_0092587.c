bb_displayroutes(int noresolve, int netstatfmt)
{
	char devname[64], flags[16], *sdest, *sgw;
	unsigned long d, g, m;
	int flgs, ref, use, metric, mtu, win, ir;
	struct sockaddr_in s_addr;
	struct in_addr mask;

	FILE *fp = xfopen_for_read("/proc/net/route");

	printf("Kernel IP routing table\n"
	       "Destination     Gateway         Genmask         Flags %s Iface\n",
			netstatfmt ? "  MSS Window  irtt" : "Metric Ref    Use");

	if (fscanf(fp, "%*[^\n]\n") < 0) {
		goto ERROR;
	}
	while (1) {
		int r;
		r = fscanf(fp, "%63s%lx%lx%X%d%d%d%lx%d%d%d\n",
				   devname, &d, &g, &flgs, &ref, &use, &metric, &m,
				   &mtu, &win, &ir);
		if (r != 11) {
			if ((r < 0) && feof(fp)) {
				break;
			}
 ERROR:
			bb_error_msg_and_die("fscanf");
		}

		if (!(flgs & RTF_UP)) {
			continue;
		}

		set_flags(flags, (flgs & IPV4_MASK));
#ifdef RTF_REJECT
		if (flgs & RTF_REJECT) {
			flags[0] = '!';
		}
#endif

		memset(&s_addr, 0, sizeof(struct sockaddr_in));
		s_addr.sin_family = AF_INET;
		s_addr.sin_addr.s_addr = d;
		sdest = INET_rresolve(&s_addr, (noresolve | 0x8000), m);
		s_addr.sin_addr.s_addr = g;
		sgw = INET_rresolve(&s_addr, (noresolve | 0x4000), m);
		mask.s_addr = m;

		printf("%-15.15s %-15.15s %-16s%-6s", sdest, sgw, inet_ntoa(mask), flags);
		free(sdest);
		free(sgw);
		if (netstatfmt) {
			printf("%5d %-5d %6d %s\n", mtu, win, ir, devname);
		} else {
			printf("%-6d %-2d %7d %s\n", metric, ref, use, devname);
		}
	}
}
