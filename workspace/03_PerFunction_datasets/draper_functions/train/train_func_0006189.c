show_scc_log(void)
{
	double	dcycs;
	int	regnum;
	int	pos;
	int	i;

	pos = g_scc_log_pos;
	dcycs = g_cur_dcycs;
	printf("SCC log pos: %d, cur dcycs:%f\n", pos, dcycs);
	for(i = 0; i < LEN_SCC_LOG; i++) {
		pos--;
		if(pos < 0) {
			pos = LEN_SCC_LOG - 1;
		}
		regnum = g_scc_log[pos].regnum;
		printf("%d:%d: port:%d wr:%d reg: %d val:%02x at t:%f\n",
			i, pos, (regnum >> 4) & 0xf, (regnum >> 8),
			(regnum & 0xf),
			g_scc_log[pos].val,
			g_scc_log[pos].dcycs - dcycs);
	}
}
