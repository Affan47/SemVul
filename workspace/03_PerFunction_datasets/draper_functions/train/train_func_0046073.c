ganv_edge_new(GanvCanvas* canvas,
              GanvNode*   tail,
              GanvNode*   head,
              const char* first_prop_name, ...)
{
	GanvEdge* edge = GANV_EDGE(
		g_object_new(ganv_edge_get_type(), NULL));

	va_list args;
	va_start(args, first_prop_name);
	ganv_item_construct(&edge->item,
	                    GANV_ITEM(ganv_canvas_get_root(canvas)),
	                    first_prop_name, args);
	va_end(args);

	edge->impl->tail = tail;
	edge->impl->head = head;

	if (!edge->impl->ghost) {
		ganv_canvas_add_edge(canvas, edge);
	}
	return edge;
}
