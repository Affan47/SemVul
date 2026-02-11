reposition_answer() {
  int i;
  int xOffset = 0;
  GooCanvasItem * item = NULL;

  if(!gcomprisBoard)
    return;

  for (i=0; i<g_list_length(item_answer_list); i++) {
    GooCanvasBounds bounds;
    item = g_list_nth_data(item_answer_list,i);
    goo_canvas_item_get_bounds(item, &bounds);
    goo_canvas_item_translate(item, xOffset-bounds.x1, line[0]-bounds.y2);
    xOffset += bounds.x2 - bounds.x1;
  }
}
