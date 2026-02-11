_gfxwop_container_free(gfxw_widget_t *widget)
{
	gfxw_container_t *container = (gfxw_container_t *) widget;
	gfxw_widget_t *seeker = container->contents;

	while (seeker) {
		gfxw_widget_t *next = seeker->next;
		seeker->widfree(seeker);
		seeker = next;
	}

	recursively_free_dirty_rects(container->dirty);
	container->dirty = NULL;

	return _gfxwop_basic_free(widget);
}
