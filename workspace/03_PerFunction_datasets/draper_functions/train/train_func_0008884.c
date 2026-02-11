lsr_get_vluimsbf5_size(u32 val, u32 extra_words)
{
	u32 nb_words;
	u32 nb_bits = val ? gf_get_bit_size(val) : 1;
	nb_words = nb_bits / 4;
	if (nb_bits%4) nb_words++;
	nb_words += extra_words;
	return 4*nb_words + nb_words;
}
