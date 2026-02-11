start_board (GcomprisBoard *agcomprisBoard)
{

  if(agcomprisBoard!=NULL)
    {
      GcomprisProperties *properties = gc_prop_get ();

      gcomprisBoard=agcomprisBoard;
      gcomprisBoard->level=1;
      gcomprisBoard->maxlevel=6;
      gcomprisBoard->sublevel=1;
      gcomprisBoard->number_of_sublevel=10;
      gc_bar_set(GC_BAR_LEVEL);


      CoverPixmap[0] = gc_rsvg_load("erase/transparent_square.svgz");
      CoverPixmap[1] = gc_rsvg_load("erase/transparent_square_green.svgz");
      CoverPixmap[2] = gc_rsvg_load("erase/transparent_square_yellow.svgz");

      event_handle_id =
	g_signal_connect(goo_canvas_get_root_item(gcomprisBoard->canvas),
			 "button_press_event",
			 (GCallback) canvas_event, NULL);

      if (strcmp(gcomprisBoard->mode,"clic")==0)
	board_mode = CLIC;
      else if (strcmp(gcomprisBoard->mode,"doubleclic")==0)
	board_mode = DOUBLECLIC;
      else {
	board_mode = NORMAL;
	gcomprisBoard->maxlevel=8;
      }

      init_user_dir();
      load_image_from_dir(properties->package_data_dir, &image_list);
      load_image_from_dir(properties->user_dir, &image_list);
      current_image = 0;

      if ( g_slist_length(image_list) == 0)
	{
	  gc_dialog(_("Error: No images found\n"), gc_board_stop);
	}
      else
	{

	  erase_next_level();

	  gamewon = FALSE;
	  pause_board(FALSE);
	}
    }
}
