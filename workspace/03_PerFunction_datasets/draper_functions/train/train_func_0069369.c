canvas_event (GooCanvasItem  *item,
	      GooCanvasItem  *target,
	      GdkEventButton *event,
	      gpointer data)
{
  if (!gcomprisBoard || board_paused || gamewon)
    return FALSE;

  if (board_mode == NORMAL)
    {
      int x = event->x;
      int y = event->y;
      int item_x = x / (BOARDWIDTH/number_of_item_x);
      int item_y = y / ((BOARDHEIGHT-BARHEIGHT)/number_of_item_y);

      if (items_per_cell[item_x * number_of_item_x + item_y] == 0)
	add_one_item(x, y, 1);

    }

  return FALSE;
}
