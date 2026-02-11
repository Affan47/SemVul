gth_image_dragger_button_release (GthImageViewerTool *self,
				  GdkEventButton     *event)
{
	GthImageDragger *dragger;
	GthImageViewer  *viewer;

	if ((event->button != 1) && (event->button != 2))
		return FALSE;

	dragger = (GthImageDragger *) self;
	viewer = dragger->priv->viewer;

	if (viewer->dragging)
		gdk_device_ungrab (event->device, event->time);

	return TRUE;
}
