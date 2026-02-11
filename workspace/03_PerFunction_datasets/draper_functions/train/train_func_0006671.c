tile_cursor(struct vc_data *vc, struct fb_info *info, int mode,
			int softback_lines, int fg, int bg)
{
	struct fb_tilecursor cursor;
	int use_sw = (vc->vc_cursor_type & 0x10);

	cursor.sx = vc->vc_x;
	cursor.sy = vc->vc_y;
	cursor.mode = (mode == CM_ERASE || use_sw) ? 0 : 1;
	cursor.fg = fg;
	cursor.bg = bg;

	switch (vc->vc_cursor_type & 0x0f) {
	case CUR_NONE:
		cursor.shape = FB_TILE_CURSOR_NONE;
		break;
	case CUR_UNDERLINE:
		cursor.shape = FB_TILE_CURSOR_UNDERLINE;
		break;
	case CUR_LOWER_THIRD:
		cursor.shape = FB_TILE_CURSOR_LOWER_THIRD;
		break;
	case CUR_LOWER_HALF:
		cursor.shape = FB_TILE_CURSOR_LOWER_HALF;
		break;
	case CUR_TWO_THIRDS:
		cursor.shape = FB_TILE_CURSOR_TWO_THIRDS;
		break;
	case CUR_BLOCK:
	default:
		cursor.shape = FB_TILE_CURSOR_BLOCK;
		break;
	}

	info->tileops->fb_tilecursor(info, &cursor);
}
