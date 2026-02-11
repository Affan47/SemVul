gog_color_scale_set_orientation (GogColorScale *scale, gboolean horizontal)
{
	GogObjectPosition pos;
	GogObject *gobj = GOG_OBJECT (scale);
	GSList *l, *ptr;
	GOStyle *style;
	scale->horizontal = horizontal;

	pos = gog_object_get_position_flags (gobj, GOG_POSITION_MANUAL);
	if (!pos) {
		gboolean changed = TRUE;
		pos = gog_object_get_position_flags (gobj, GOG_POSITION_COMPASS);
		switch (pos) {
		case GOG_POSITION_N:
			pos = GOG_POSITION_W;
			break;
		case GOG_POSITION_S:
			pos = GOG_POSITION_E;
			break;
		case GOG_POSITION_E:
			pos = GOG_POSITION_S;
			break;
		case GOG_POSITION_W:
			pos = GOG_POSITION_N;
			break;
		default:
			changed = FALSE;
		}
		if (changed)
			gog_object_set_position_flags (gobj, pos, GOG_POSITION_COMPASS);
	}
	pos = gog_object_get_position_flags (gobj, GOG_POSITION_ANY_MANUAL_SIZE);
	if (pos) {
		GogViewAllocation alloc;
		double buf;
		switch (pos) {
		case GOG_POSITION_MANUAL_W:
			gog_object_set_position_flags (gobj, GOG_POSITION_MANUAL_H,
				                           GOG_POSITION_ANY_MANUAL_SIZE);
			break;
		case GOG_POSITION_MANUAL_W_ABS:
			gog_object_set_position_flags (gobj, GOG_POSITION_MANUAL_H_ABS,
				                           GOG_POSITION_ANY_MANUAL_SIZE);
			break;
		case GOG_POSITION_MANUAL_H:
			gog_object_set_position_flags (gobj, GOG_POSITION_MANUAL_W,
				                           GOG_POSITION_ANY_MANUAL_SIZE);
			break;
		case GOG_POSITION_MANUAL_H_ABS:
			gog_object_set_position_flags (gobj, GOG_POSITION_MANUAL_W_ABS,
				                           GOG_POSITION_ANY_MANUAL_SIZE);
			break;
		default:
			break;
		}
		gog_object_get_manual_position (gobj, &alloc);
		buf = alloc.w;
		alloc.w = alloc.h;
		alloc.h = buf;
       	gog_object_set_manual_position (gobj, &alloc);
	}
	l = gog_object_get_children (gobj, NULL);
	for (ptr = l; ptr; ptr = ptr->next) {
		if (GO_IS_STYLED_OBJECT (ptr->data)) {
			style = go_style_dup (go_styled_object_get_style (ptr->data));
			go_styled_object_set_style (ptr->data, style);
			g_object_unref (style);
		}
	}
	g_slist_free (l);
}
