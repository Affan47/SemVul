ganv_node_default_disconnect(GanvNode* node)
{
	GanvCanvas* canvas = GANV_CANVAS(GANV_ITEM(node)->canvas);
	if (canvas) {
		ganv_canvas_for_each_edge_on(
			canvas, node, (GanvEdgeFunc)ganv_edge_disconnect, NULL);
	}
}
