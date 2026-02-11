kmx61_convert_freq_to_bit(int val, int val2)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(kmx61_samp_freq_table); i++)
		if (val == kmx61_samp_freq_table[i].val &&
		    val2 == kmx61_samp_freq_table[i].val2)
			return i;
	return -EINVAL;
}
