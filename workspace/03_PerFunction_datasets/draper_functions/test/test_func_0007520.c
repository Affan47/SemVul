pulse_width_count_to_us(u16 count, u16 divider)
{
	u64 n;
	u32 rem;


	n = (((u64) count << 2) | 0x3) * (divider + 1);
	rem = do_div(n, CX23888_IR_REFCLK_FREQ / 1000000);
	if (rem >= CX23888_IR_REFCLK_FREQ / 1000000 / 2)
		n++;
	return (unsigned int) n;
}
