gth_file_tool_rotate_left_activate (GthFileTool *base)
{
	GtkWidget       *window;
	GtkWidget       *viewer_page;
	GtkWidget       *viewer;
	cairo_surface_t *old_image;
	cairo_surface_t *new_image;

	window = gth_file_tool_get_window (base);
	viewer_page = gth_browser_get_viewer_page (GTH_BROWSER (window));
	if (! GTH_IS_IMAGE_VIEWER_PAGE (viewer_page))
		return;

	viewer = gth_image_viewer_page_get_image_viewer (GTH_IMAGE_VIEWER_PAGE (viewer_page));
	old_image = gth_image_viewer_get_current_image (GTH_IMAGE_VIEWER (viewer));
	if (old_image == NULL)
		return;

	new_image = _cairo_image_surface_transform (old_image, GTH_TRANSFORM_ROTATE_270);
	gth_image_viewer_page_set_image (GTH_IMAGE_VIEWER_PAGE (viewer_page), new_image, TRUE);

	cairo_surface_destroy (new_image);
}
