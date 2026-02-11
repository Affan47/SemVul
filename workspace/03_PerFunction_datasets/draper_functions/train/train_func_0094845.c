nemo_icon_container_layout_now (NemoIconContainer *container)
{
	if (container->details->idle_id != 0) {
		unschedule_redo_layout (container);
		redo_layout_internal (container);
	}


	gtk_container_check_resize (GTK_CONTAINER (gtk_widget_get_parent (GTK_WIDGET (container))));
}
