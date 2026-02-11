stripnl2uni(struct convert_rock *rock, int c)
{
    if (c != '\r' && c != '\n')
	convert_putc(rock->next, c);
}
