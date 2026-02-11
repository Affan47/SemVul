pan_item_box_shadow(PanItem *pi, gint offset, gint fade)
{
	gint *shadow;

	if (!pi || pi->type != PAN_ITEM_BOX) return;

	shadow = pi->data;
	if (shadow)
		{
		pi->width -= shadow[0];
		pi->height -= shadow[0];
		}

	shadow = g_new0(gint, 2);
	shadow[0] = offset;
	shadow[1] = fade;

	pi->width += offset;
	pi->height += offset;

	g_free(pi->data);
	pi->data = shadow;
}
