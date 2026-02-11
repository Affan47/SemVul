start_board (GcomprisBoard *agcomprisBoard)
{

  if(agcomprisBoard!=NULL)
    {
      gcomprisBoard=agcomprisBoard;
      gcomprisBoard->level=1;
      gcomprisBoard->sublevel=1;
      gcomprisBoard->number_of_sublevel=10;
      gc_bar_set(GC_BAR_LEVEL);
      gc_bar_location(0, -1, 0.6);


      if(!gcomprisBoard->mode)
	{
	  gcomprisBoard->maxlevel=9;
	  currentMode=WITHOUT_CENTS;
	}
      else if(g_strcmp0(gcomprisBoard->mode, "WITH_CENTS")==0)
	{
	  gcomprisBoard->maxlevel=5;
	  currentMode=WITH_CENTS;
	}
      else if(g_strcmp0(gcomprisBoard->mode, "BACK_WITHOUT_CENTS")==0)
	{
	  gcomprisBoard->maxlevel=9;
	  currentMode=BACK_WITHOUT_CENTS;
	}
      else if(g_strcmp0(gcomprisBoard->mode, "BACK_WITH_CENTS")==0)
	{
	  gcomprisBoard->maxlevel=5;
	  currentMode=BACK_WITH_CENTS;
	}
      money_next_level();

      gamewon = FALSE;
      pause_board(FALSE);
    }
}
