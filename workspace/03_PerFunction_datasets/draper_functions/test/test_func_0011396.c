nemo_icon_container_set_layout_mode (NemoIconContainer *container,
					 NemoIconLayoutMode mode)
{
	g_return_if_fail (NEMO_IS_ICON_CONTAINER (container));

	container->details->layout_mode = mode;
	invalidate_labels (container);

	container->details->needs_resort = TRUE;
	redo_layout (container);

	g_signal_emit (container, signals[LAYOUT_CHANGED], 0);
}
