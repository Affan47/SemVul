image_osd_histogram_toggle_channel(ImageWindow *imd)
{
	OverlayStateData *osd = image_get_osd_data(imd);

	if (!osd || !osd->histogram) return;

	histogram_toggle_channel(osd->histogram);
	image_osd_update(imd);
}
