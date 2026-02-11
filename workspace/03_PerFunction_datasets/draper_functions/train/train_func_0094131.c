wnd_scan_color()
{
	int cnt;
	byte *src, *dest;
	int *tile;

	if (WX >= 160) return;
	cnt = 160 - WX;
	tile = WND;
	dest = BUF + WX;

	while (cnt >= 8)
	{
		src = patpix[*(tile++)][WV];
		blendcpy(dest, src, *(tile++), 8);
		dest += 8;
		cnt -= 8;
	}
	src = patpix[*(tile++)][WV];
	blendcpy(dest, src, *(tile++), cnt);
}
