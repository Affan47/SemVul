_gcr_display_view_real_get_renderer (GcrViewer *viewer, guint index_)
{
	GcrDisplayView *self = GCR_DISPLAY_VIEW (viewer);
	g_return_val_if_fail (index_ < self->pv->renderers->len, NULL);
	return g_ptr_array_index (self->pv->renderers, index_);
}
