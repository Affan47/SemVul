arcfb_lcd_update_vert(struct arcfb_par *par, unsigned int top,
		unsigned int bottom, unsigned int left, unsigned int right)
{
	unsigned int distance, upper, lower;

	distance = (bottom - top) + 1;
	upper = top;
	lower = top + 7;

	while (distance > 0) {
		distance -= 8;
		arcfb_lcd_update_page(par, upper, left, right, 8);
		upper = lower + 1;
		lower = upper + 7;
	}
}
