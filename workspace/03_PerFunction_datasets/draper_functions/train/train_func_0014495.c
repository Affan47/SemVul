filter_view_set_bounds (SheetObjectView *sov, double const *coords, gboolean visible)
{
	GocGroup *view = GOC_GROUP (sov);

	if (visible) {
		double scale = goc_canvas_get_pixels_per_unit (GOC_ITEM (view)->canvas);
		double h = (coords[3] - coords[1]) + 1.;
		if (h > 20.)
			h = 20.;
		h /= scale;
		goc_item_set (GOC_ITEM (view->children->data),

			"x",	  ((coords[2] >= 0.) ? (coords[2] / scale - h + 1) : coords[0] / scale),
			"y",	  coords [3] / scale - h + 1.,
			"width",  h,
			"height", h,
			NULL);

		goc_item_show (GOC_ITEM (view));
	} else
		goc_item_hide (GOC_ITEM (view));
}
