summarize_uvhub_sockets(int nuvhubs,
			struct uvhub_desc *uvhub_descs,
			unsigned char *uvhub_mask)
{
	int socket;
	int uvhub;
	unsigned short socket_mask;

	for (uvhub = 0; uvhub < nuvhubs; uvhub++) {
		struct uvhub_desc *bdp;
		struct bau_control *smaster = NULL;
		struct bau_control *hmaster = NULL;

		if (!(*(uvhub_mask + (uvhub/8)) & (1 << (uvhub%8))))
			continue;

		bdp = &uvhub_descs[uvhub];
		socket_mask = bdp->socket_mask;
		socket = 0;
		while (socket_mask) {
			struct socket_desc *sdp;
			if ((socket_mask & 1)) {
				sdp = &bdp->socket[socket];
				if (scan_sock(sdp, bdp, &smaster, &hmaster))
					return 1;
				make_per_cpu_thp(smaster);
			}
			socket++;
			socket_mask = (socket_mask >> 1);
		}
		make_per_hub_cpumask(hmaster);
	}
	return 0;
}
