BIG5(u_char ch1, u_char ch2)
{
    if (ch2 < 0xA1)
	return(((ch1 - 0xA1) * 157 + ch2 - 0x40) << 5);
    else
	return(((ch1 - 0xA1) * 157 + 63 + ch2 - 0xA1) << 5);
}
