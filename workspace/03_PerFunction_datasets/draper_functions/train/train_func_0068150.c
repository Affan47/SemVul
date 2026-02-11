redrat3_us_to_len(u32 microsec)
{
	u32 result;
	u32 divisor;

	microsec = (microsec > IR_MAX_DURATION) ? IR_MAX_DURATION : microsec;
	divisor = (RR3_CLK_CONV_FACTOR / 1000);
	result = (u32)(microsec * divisor) / 1000;


	return result ? result : 1;
}
