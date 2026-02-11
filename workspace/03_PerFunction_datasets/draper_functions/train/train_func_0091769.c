scroll_region(u16 start_y, u16 end_y, s16 num)
{
	s32 y, takey, fast_scroll, mx, clr;
	u16 temp[height];
	u16 temp_sx[height], temp_ex[height];

	if (!num) return;
	if (end_y >= height) end_y = height - 1;
	if (start_y > end_y) return;

	mx = end_y-start_y+1;
	if (num > mx) num = mx;
	if (-num > mx) num = -mx;

	if (start_y == 0 && num > 0) {
		history_scroll(num);
	}

	fast_scroll = (start_y == scroll_top && end_y == scroll_bot);

	if (fast_scroll) pending_scroll += num;

	memcpy(temp, linenumbers, sizeof(temp));
	if (fast_scroll) {
		memcpy(temp_sx, dirty_startx, sizeof(temp_sx));
		memcpy(temp_ex, dirty_endx, sizeof(temp_ex));
	}


	if (num<mx && -num<mx) {
		for (y=start_y; y<=end_y; y++) {
			takey = y+num;
			clr = (takey<start_y) || (takey>end_y);
			if (takey<start_y) takey = end_y+1-(start_y-takey);
			if (takey>end_y) takey = start_y-1+(takey-end_y);

			linenumbers[y] = temp[takey];

			if (!fast_scroll || clr) {
				dirty_startx[y] = 0;
				dirty_endx[y] = width-1;
			} else {
				dirty_startx[y] = temp_sx[takey];
				dirty_endx[y] = temp_ex[takey];
			}

			if (clr) {
				clear_area(0, y, width - 1, y);
			}
		}
	}
}
