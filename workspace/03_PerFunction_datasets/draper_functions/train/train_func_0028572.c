rpm_from_cnt(u8 val, u32 clk, u16 div)
{
	return ((val == 0x00) ? 0 : ((clk*30)/(val*div)));
}
