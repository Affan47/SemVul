insert(adv_scroll_info* info, int x, int y)
{
	if (info->mac == info->max) {
		info->max *= 2;
		if (!info->max)
			info->max = 64;
		info->map = (adv_scroll_coord*)realloc(info->map, info->max * sizeof(adv_scroll_coord));
	}

	info->map[info->mac].x = x;
	info->map[info->mac].y = y;
	++info->mac;
}
