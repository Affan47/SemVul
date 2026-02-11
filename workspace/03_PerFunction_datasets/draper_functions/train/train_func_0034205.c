size_allocate (GtkWidget *widget,
	       GtkAllocation *allocation)
{
	NautilusCanvasContainer *container;
	gboolean need_layout_redone;
	GtkAllocation wid_allocation;

	container = NAUTILUS_CANVAS_CONTAINER (widget);

	need_layout_redone = !container->details->has_been_allocated;
	gtk_widget_get_allocation (widget, &wid_allocation);

	if (allocation->width != wid_allocation.width) {
		need_layout_redone = TRUE;
	}

	if (allocation->height != wid_allocation.height) {
		need_layout_redone = TRUE;
	}


	if (container->details->size_allocation_count_id == 0) {
		container->details->size_allocation_count_id =
			g_idle_add_full  (G_PRIORITY_HIGH,
					  clear_size_allocation_count,
					  container, NULL);
	}
	container->details->size_allocation_count++;
	if (container->details->size_allocation_count > 2 &&
	    allocation->width >= wid_allocation.width) {
		need_layout_redone = FALSE;
	}

	GTK_WIDGET_CLASS (nautilus_canvas_container_parent_class)->size_allocate (widget, allocation);

	container->details->has_been_allocated = TRUE;

	if (need_layout_redone) {
		redo_layout (container);
	}
}
