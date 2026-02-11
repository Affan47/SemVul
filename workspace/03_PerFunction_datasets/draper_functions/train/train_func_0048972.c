rb_segmented_bar_size_allocate(GtkWidget *widget, GtkAllocation *allocation)
{
	gint real_height;
	RBSegmentedBarPrivate *priv = RB_SEGMENTED_BAR_GET_PRIVATE (widget);
	GtkAllocation new_allocation;

	g_return_if_fail(RB_IS_SEGMENTED_BAR(widget));
	g_return_if_fail(allocation != NULL);

	if (priv->reflect) {
		real_height = priv->bar_height*1.75;
	} else {
		real_height = priv->bar_height;
	}
	gtk_widget_set_allocation (widget, allocation);
	if (priv->show_labels) {
		compute_layout_size (RB_SEGMENTED_BAR (widget));
		new_allocation.height = MAX (priv->bar_height + priv->bar_label_spacing + priv->layout_height,
		                         real_height);
	} else {
		new_allocation.height = real_height;
	}
	new_allocation.width = priv->layout_width + 2*(priv->h_padding);
	gtk_widget_set_allocation (widget, &new_allocation);
	GTK_WIDGET_CLASS(rb_segmented_bar_parent_class)->size_allocate(widget, allocation);
}
