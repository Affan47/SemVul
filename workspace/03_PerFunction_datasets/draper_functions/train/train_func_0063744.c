border_draw_part_marks(
	border_relief_descr *br, rectangle *part_g, window_parts part,
	Pixmap dest_pix)
{
	int l;
	int t;
	int w;
	int h;
	int o;

	l = br->sidebar_g.x;
	t = br->sidebar_g.y;
	w = part_g->width;
	h = part_g->height;
	o = br->marks.offset_br;
	switch (part)
	{
	case PART_BORDER_N:
		border_draw_y_mark(br, 0, 0, dest_pix, False);
		border_draw_y_mark(br, w, 0, dest_pix, True);
		break;
	case PART_BORDER_S:
		border_draw_y_mark(br, 0, h + o, dest_pix, False);
		border_draw_y_mark(br, w, h + o, dest_pix, True);
		break;
	case PART_BORDER_E:
		border_draw_x_mark(br, w + o, 0, dest_pix, False);
		border_draw_x_mark(br, w + o, h, dest_pix, True);
		break;
	case PART_BORDER_W:
		border_draw_x_mark(br, 0, 0, dest_pix, False);
		border_draw_x_mark(br, 0, h, dest_pix, True);
		break;
	case PART_BORDER_NW:
		border_draw_x_mark(br, 0, t, dest_pix, True);
		border_draw_y_mark(br, l, 0, dest_pix, True);
		break;
	case PART_BORDER_NE:
		border_draw_x_mark(br, l + o, t, dest_pix, True);
		border_draw_y_mark(br, 0, 0, dest_pix, False);
		break;
	case PART_BORDER_SW:
		border_draw_x_mark(br, 0, 0, dest_pix, False);
		border_draw_y_mark(br, l, t + o, dest_pix, True);
		break;
	case PART_BORDER_SE:
		border_draw_x_mark(br, l + o, 0, dest_pix, False);
		border_draw_y_mark(br, 0, t + o, dest_pix, False);
		break;
	default:
		return;
	}

	return;
}
