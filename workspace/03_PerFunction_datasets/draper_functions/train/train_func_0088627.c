shapegame_next_level()
{
  char *filename;

  gamewon = FALSE;
  gc_drag_stop(goo_canvas_get_root_item(gcomprisBoard->canvas));

  shapegame_destroy_all_items();
  next_shapelist_item = previous_shapelist_item = NULL;
  shapegame_init_canvas(goo_canvas_get_root_item(gcomprisBoard->canvas));

  while( ((filename = gc_file_find_absolute("%s/board%d_%d.xml",
					    gcomprisBoard->boarddir,
					    gcomprisBoard->level,
					    gcomprisBoard->sublevel,
					    NULL)) == NULL)
	 && ((gcomprisBoard->level != 1) || (gcomprisBoard->sublevel!=0)))
    {

      gcomprisBoard->sublevel = gcomprisBoard->number_of_sublevel;
      if(!increment_sublevel())
	{
	  g_free(filename);
	  return;
	}
    }

  gc_bar_set_level(gcomprisBoard);

  read_xml_file(filename);
  gc_drag_start(goo_canvas_get_root_item(gcomprisBoard->canvas),
		(GcDragFunc) item_event_drag, drag_mode);
  g_free(filename);
}
