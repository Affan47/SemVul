gth_image_dragger_draw (GthImageViewerTool *self,
		        cairo_t            *cr)
{
	GthImageDragger *dragger;
	GthImageViewer  *viewer;

	dragger = (GthImageDragger *) self;
	viewer = dragger->priv->viewer;

	gth_image_viewer_paint_background (viewer, cr);

	if (gth_image_viewer_get_current_image (viewer) == NULL)
		return;

	if (dragger->priv->scaled != NULL)
		gth_image_viewer_paint_region (viewer,
					       cr,
					       dragger->priv->scaled,
					       viewer->x_offset - viewer->image_area.x,
					       viewer->y_offset - viewer->image_area.y,
					       &viewer->image_area,
					       NULL,
					       CAIRO_FILTER_FAST);
	else
		gth_image_viewer_paint_region (viewer,
					       cr,
					       gth_image_viewer_get_current_image (viewer),
					       viewer->x_offset - viewer->image_area.x,
					       viewer->y_offset - viewer->image_area.y,
					       &viewer->image_area,
					       NULL,
					       gth_image_viewer_get_zoom_quality_filter (viewer));

	gth_image_viewer_apply_painters (viewer, cr);
}
