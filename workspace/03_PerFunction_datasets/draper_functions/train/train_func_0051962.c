ganv_widget_bounds(GanvItem* item, double* x1, double* y1, double* x2, double* y2)
{
	GanvWidget* witem = GANV_WIDGET(item);

	*x1 = witem->x;
	*y1 = witem->y;

	switch (witem->anchor) {
	case GTK_ANCHOR_NW:
	case GTK_ANCHOR_W:
	case GTK_ANCHOR_SW:
		break;

	case GTK_ANCHOR_N:
	case GTK_ANCHOR_CENTER:
	case GTK_ANCHOR_S:
		*x1 -= witem->width / 2.0;
		break;

	case GTK_ANCHOR_NE:
	case GTK_ANCHOR_E:
	case GTK_ANCHOR_SE:
		*x1 -= witem->width;
		break;

	default:
		break;
	}

	switch (witem->anchor) {
	case GTK_ANCHOR_NW:
	case GTK_ANCHOR_N:
	case GTK_ANCHOR_NE:
		break;

	case GTK_ANCHOR_W:
	case GTK_ANCHOR_CENTER:
	case GTK_ANCHOR_E:
		*y1 -= witem->height / 2.0;
		break;

	case GTK_ANCHOR_SW:
	case GTK_ANCHOR_S:
	case GTK_ANCHOR_SE:
		*y1 -= witem->height;
		break;

	default:
		break;
	}

	*x2 = *x1 + witem->width;
	*y2 = *y1 + witem->height;
}
