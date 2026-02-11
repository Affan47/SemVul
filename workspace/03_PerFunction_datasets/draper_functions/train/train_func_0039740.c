rt_overlay_queue_all(RendererTiles *rt, gint x1, gint y1, gint x2, gint y2)
{
	GList *work;

	work = rt->overlay_list;
	while (work)
		{
		OverlayData *od = work->data;
		work = work->next;

		rt_overlay_queue_draw(rt, od, x1, y1, x2, y2);
		}
}
