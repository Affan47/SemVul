gx_fast_meter_size_request (GtkWidget* wd, GtkRequisition* req)
{
	req->height = min_size;
	req->width  = GX_FAST_METER(wd)->dimen;
	if (req->width == 0) {
		gtk_widget_style_get(wd, "dimen", &req->width, NULL);
	}
}
