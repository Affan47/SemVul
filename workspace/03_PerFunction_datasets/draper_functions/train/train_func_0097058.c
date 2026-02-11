rtw_freq2ch(u32 freq)
{
	u8	i;
	u32	ch = 0;

	for (i = 0; i < ch_freq_map_num; i++) {
		if (freq == ch_freq_map[i].frequency) {
			ch = ch_freq_map[i].channel;
				break;
		}
	}
	if (i == ch_freq_map_num)
		ch = 1;

	return ch;
}
