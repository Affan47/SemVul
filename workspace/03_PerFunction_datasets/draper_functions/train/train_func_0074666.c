goto_start_of_line(void)
{
	while (HS.pos > HS.buf)
		back_over_char((int)(*--HS.pos));
}
