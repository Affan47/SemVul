gt_to_alignment(double halign, double valign)
{
	int align = 0;

	if (halign == 0.0)
		align += 0x1;
	else if (halign == 0.5)
		align += 0x2;
	else if (halign == 1.0)
		align += 0x3;

	if (valign == 0.0)
		align += 0x10;
	else if (valign == 1.0)
		align += 0x20;

	return align;
}
