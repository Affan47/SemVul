move_item_at(GooCanvasItem *item, int block, double ratio)
{
  double block_width, block_height;
  int i,j;
  GooCanvasBounds bounds;

  block_width  = BOARDWIDTH/number_of_item_x;
  block_height = (BOARDHEIGHT-BARHEIGHT)/number_of_item_y;

  if(block < number_of_item_x)
    {

      g_warning("      // Upper line\n");
      i = block_width * block;
      j = 0;
    }
  else if(block < number_of_item_x + number_of_item_y - 2)
    {

      g_warning("      // Right line\n");
      i = block_width * (number_of_item_x - 1);
      j = block_height * (block - (number_of_item_x-1));
    }
  else if(block < number_of_item_x*2 + number_of_item_y - 2)
    {

      g_warning("      // Bottom line\n");
      i = block_width * (number_of_item_x - (block-
					     (number_of_item_x+number_of_item_y-1))-2);
      j = block_height * (number_of_item_y-1);
    }
  else
    {

      g_warning("      // Left line\n");
      i = 0;
      j = block_height * (number_of_item_y - (block - (number_of_item_x*2 +
						      number_of_item_y-4)));
    }

  g_warning("move_item_at %d i=%d j=%d\n", block, i, j);

  goo_canvas_item_get_bounds(item, &bounds);

  goo_canvas_item_animate(item,
			  i,
			  j,
			  1.0,
			  0,
			  TRUE,
			  animate_speed,
			  40,
			  GOO_CANVAS_ANIMATE_FREEZE);

}
