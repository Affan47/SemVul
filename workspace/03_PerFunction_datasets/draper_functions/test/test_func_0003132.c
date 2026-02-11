putld(d, base)
long	d;
int	base;
{
	int	len = 1;
	long	tmpd = d;

	if (current_fmt.width == 0 && current_fmt.precision) {
		current_fmt.width = current_fmt.precision;
		current_fmt.padc = '0';
	}
	while ((tmpd = (tmpd / base)) != 0)
		len += 1;
	if (d < 0)
		len += 1;
	if (!current_fmt.leftadj)
		pad(current_fmt.padc, current_fmt.width - len);
	if (d < 0) {
		f_putc('-', current_fmt.iop);
		d = -d;
	}
	outld(d, base);
	if (current_fmt.leftadj)
		pad(current_fmt.padc, current_fmt.width - len);
}
