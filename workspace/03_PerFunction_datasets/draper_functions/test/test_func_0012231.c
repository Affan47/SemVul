check_a2vid_palette()
{
	int	sum;
	int	min;
	int	val;
	int	min_pos;
	int	count_cur;
	int	i;


	g_num_a2vid_palette_checks--;
	if(g_num_a2vid_palette_checks || g_installed_full_superhires_colormap){
		return;
	}

	g_num_a2vid_palette_checks = 60;

	sum = 0;
	min = 0x100000;
	min_pos = -1;
	count_cur = g_shr_palette_used[g_a2vid_palette];

	for(i = 0; i < 16; i++) {
		val = g_shr_palette_used[i];
		g_shr_palette_used[i] = 0;
		if(val < min) {
			min = val;
			min_pos = i;
		}
		sum += val;
	}

	if(g_a2vid_palette != min_pos && (count_cur > min)) {
		change_a2vid_palette(min_pos);
	}
}
