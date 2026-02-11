start_board (GcomprisBoard *agcomprisBoard)
{

  if(agcomprisBoard!=NULL)
    {
      gcomprisBoard=agcomprisBoard;

      gc_set_background(goo_canvas_get_root_item(gcomprisBoard->canvas),
			      "clockgame/clockgame-bg0.svgz");


      cx =  BOARDWIDTH/2 + 16;
      cy =  BOARDHEIGHT*0.4 + 42;
      clock_size = BOARDHEIGHT*0.3;

      gcomprisBoard->level=1;
      gcomprisBoard->maxlevel=7;
      gcomprisBoard->sublevel=1;
      gcomprisBoard->number_of_sublevel=3;
      gc_score_start(SCORESTYLE_NOTE,
		     BOARDWIDTH - 195,
		     30,
			   gcomprisBoard->number_of_sublevel);
      gc_bar_set(GC_BAR_LEVEL);
      gc_bar_location(BOARDWIDTH - 200, -1, 0.8);

      clockgame_next_level();

      gamewon = FALSE;
      pause_board(FALSE);

    }

}
