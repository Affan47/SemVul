free_composited_resources (PanelBackground *background)
{
	background->composited = FALSE;

	if (background->composited_pattern)
		cairo_pattern_destroy (background->composited_pattern);
	background->composited_pattern = NULL;
}
