draw_clock(pixelfield_t &pf, bool seconds=true)
{
	int cw, ch;
	get_clock_dimensions(cw, ch, seconds);
	int x = (pf.width - cw) / 2;
	int y = (pf.height - ch) / 2 + 1;

	int hour[2];
	int minute[2];
	int second[2];
	time_t ti = time(NULL);
	struct tm* tt = localtime(&ti);

	hour[0] = tt->tm_hour / 10;
	hour[1] = tt->tm_hour % 10;
	minute[0] = tt->tm_min / 10;
	minute[1] = tt->tm_min % 10;
	second[0] = tt->tm_sec / 10;
	second[1] = tt->tm_sec % 10;

	draw_digit(pf, x+1, y, TB_GREEN, hour[0]);
	draw_digit(pf, x+5, y, TB_GREEN, hour[1]);
	draw_digit(pf, x+8, y, TB_GREEN, 10);
	draw_digit(pf, x+11, y, TB_GREEN, minute[0]);
	draw_digit(pf, x+15, y, TB_GREEN, minute[1]);
	if (seconds) {
		draw_digit(pf, x+18, y, TB_GREEN, 10);
		draw_digit(pf, x+21, y, TB_GREEN, second[0]);
		draw_digit(pf, x+25, y, TB_GREEN, second[1]);
	}
}
