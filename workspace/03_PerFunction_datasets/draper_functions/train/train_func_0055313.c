start_board (GcomprisBoard *agcomprisBoard)
{
  gchar *filename = NULL;
  gboolean default_background = TRUE;

  GHashTable *config = gc_db_get_board_conf();

  if (strcmp(agcomprisBoard->name, "imagename")==0){
    gc_locale_set(g_hash_table_lookup( config, "locale"));
  }

  gchar *drag_mode_str = g_hash_table_lookup( config, "drag_mode");

  if (drag_mode_str && (strcmp (drag_mode_str, "NULL") != 0))
    drag_mode = g_ascii_strtod(drag_mode_str, NULL);
  else
    drag_mode = 0;

  g_hash_table_destroy(config);

  if(agcomprisBoard!=NULL)
    {
      gcomprisBoard = agcomprisBoard;


      gcomprisBoard->disable_im_context = TRUE;


      gcomprisBoard->level = 1;


      gcomprisBoard->maxlevel=1;

      while( (filename = gc_file_find_absolute("%s/board%d_0.xml",
					       gcomprisBoard->boarddir,
					       gcomprisBoard->maxlevel,
					       NULL)) )
	{
	  gcomprisBoard->maxlevel++;
	  g_free(filename);
	}
      g_free(filename);

      gcomprisBoard->maxlevel--;

      gc_bar_set(GC_BAR_CONFIG|GC_BAR_LEVEL);
      gc_bar_location(10, -1, 0.6);


      gcomprisBoard->sublevel = 0;


      gcomprisBoard->number_of_sublevel=G_MAXINT;


      if(gcomprisBoard->mode!=NULL)
	if(g_ascii_strncasecmp(gcomprisBoard->mode, "background=", 11)==0)
	  {
	    gchar *tmp = NULL;

	    tmp = g_malloc(strlen(gcomprisBoard->mode));
	    tmp = strcpy(tmp, gcomprisBoard->mode + 11);

	    gc_set_background(goo_canvas_get_root_item(gcomprisBoard->canvas), tmp);
	    default_background = FALSE;
	    g_free(tmp);
	  }

      if(default_background)
	{

	  gc_set_default_background(goo_canvas_get_root_item(gcomprisBoard->canvas));
	}


      selector_item =
	goo_canvas_svg_new (goo_canvas_get_root_item(gcomprisBoard->canvas),
			    gc_skin_rsvg_get(),
			    "svg-id", "#SELECTOR",
			    "pointer-events", GOO_CANVAS_EVENTS_NONE,
			    NULL);


      gc_drag_start(goo_canvas_get_root_item(gcomprisBoard->canvas),
		    (GcDragFunc) item_event_drag, drag_mode);
      shapegame_next_level();

      pause_board(FALSE);

    }
}
