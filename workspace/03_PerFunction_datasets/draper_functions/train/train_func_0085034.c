od_multibutton_size_request(GtkWidget *widget, GtkRequisition *req)
{
	ODMultiButton	*mb;
	gint		focus_width, focus_pad;

	g_return_if_fail(widget != NULL);
	g_return_if_fail(req != NULL);
	g_return_if_fail(OD_IS_MULTIBUTTON(widget));

	mb = OD_MULTIBUTTON(widget);

	req->width  = 2 * (gtk_container_get_border_width(GTK_CONTAINER(widget)) + 1 + gtk_widget_get_style(widget)->xthickness);
	req->height = 2 * (gtk_container_get_border_width(GTK_CONTAINER(widget)) + 1 + gtk_widget_get_style(widget)->ythickness);


	gtk_widget_style_get(GTK_WIDGET(widget), "focus-line-width", &focus_width, "focus-padding", &focus_pad, NULL);
	req->width  += 2 * (focus_width + focus_pad);
	req->height += 2 * (focus_width + focus_pad);

	od_multibutton_page_size_calc(mb);
	req->width  += mb->width;
	req->height += mb->height;
}
