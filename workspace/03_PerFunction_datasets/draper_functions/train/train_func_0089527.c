freq_to_shift(u16 freq)
{
	u32 freq_khz = freq * 1000;
	u64 max_val_cycles = freq_khz * 1000 * MLX4_EN_WRAP_AROUND_SEC;
	u64 max_val_cycles_rounded = is_power_of_2(max_val_cycles + 1) ?
		max_val_cycles : roundup_pow_of_two(max_val_cycles) - 1;

	u64 max_mul = div_u64(0xffffffffffffffffULL, max_val_cycles_rounded);


	return ilog2(div_u64(max_mul * freq_khz, 1000000));
}
