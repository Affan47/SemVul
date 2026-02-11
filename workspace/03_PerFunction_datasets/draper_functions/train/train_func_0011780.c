planegame_next_level()
{
  RsvgHandle *svg_handle = NULL;
  GooCanvasItem *item;

  gc_bar_set_level(gcomprisBoard);

  planegame_destroy_all_items();

  rootitem = goo_canvas_group_new (goo_canvas_get_root_item(gcomprisBoard->canvas),
				   NULL);

  clouds_rootitem = goo_canvas_group_new (rootitem, NULL);


  speed=100+(40/(gcomprisBoard->level));
  fallSpeed=10000-gcomprisBoard->level*200;

  imageZoom=0.3+(0.5/(gcomprisBoard->level));


  planespeed_y = 0;
  planespeed_x = 0;
  svg_handle = gc_rsvg_load("planegame/tuxhelico.svgz");
  plane_x = 50;
  plane_y = 300;

  planeitem = goo_canvas_group_new (rootitem,
				   NULL);

  goo_canvas_item_translate(planeitem, plane_x, plane_y);

  item = goo_canvas_svg_new (planeitem,
			   svg_handle,
			   NULL);

  goo_canvas_item_scale(item,
  			0.4 * imageZoom,
  			0.4 * imageZoom);

  g_object_unref(svg_handle);


  plane_target = 1;
  plane_last_target = 10;

  gcomprisBoard->number_of_sublevel=plane_last_target;

  gcomprisBoard->sublevel=plane_target;

  if(gcomprisBoard->level>1)
    {

      gc_score_end();
    }
  else
    {
      gc_score_start(SCORESTYLE_NOTE,
			   BOARDWIDTH - 195,
			   BOARDHEIGHT - 30,
			   gcomprisBoard->number_of_sublevel);
      gc_score_set(gcomprisBoard->sublevel);
    }

}
