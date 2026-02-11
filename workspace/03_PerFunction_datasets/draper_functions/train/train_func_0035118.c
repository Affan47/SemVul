gnm_soi_new_view (SheetObject *so, SheetObjectViewContainer *container)
{
	SheetObjectImage *soi = SHEET_OBJECT_IMAGE (so);
	GocItem *item = NULL;

	item = goc_item_new (
		gnm_pane_object_group (GNM_PANE (container)),
		so_image_goc_view_get_type (),
		NULL);
	if (soi->image) {
		goc_item_hide (goc_item_new (GOC_GROUP (item),
			GOC_TYPE_IMAGE,
			"image", soi->image,
		        "crop-bottom", soi->crop_bottom,
		        "crop-left", soi->crop_left,
		        "crop-right", soi->crop_right,
		        "crop-top", soi->crop_top,
			NULL));

	} else {
		GdkPixbuf *placeholder = go_gdk_pixbuf_load_from_file
			("res:gnm:pixmaps/unknown_image.png");
		GdkPixbuf *pixbuf = gdk_pixbuf_copy (placeholder);

		goc_item_hide (goc_item_new (GOC_GROUP (item),
			GOC_TYPE_PIXBUF,
			"pixbuf", pixbuf,
			NULL));
		g_object_unref (pixbuf);
		g_object_set_data (G_OBJECT (item), "tile", placeholder);
	}

	return gnm_pane_object_register (so, item, TRUE);
}
