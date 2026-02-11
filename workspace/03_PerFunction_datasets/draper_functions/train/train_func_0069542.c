start_board (GcomprisBoard *agcomprisBoard)
{

  if (agcomprisBoard != NULL) {

	gcomprisBoard = agcomprisBoard;
	gcomprisBoard->level = 1;
	gcomprisBoard->maxlevel = 9;
	gcomprisBoard->sublevel = 1;
	gcomprisBoard->number_of_sublevel = 1;
	gc_bar_set(GC_BAR_LEVEL);
	gc_bar_location(20, -1, 0.7);

	if (strcmp(gcomprisBoard->mode, "minus") == 0)
		board_mode = MODE_MINUS;
	else if (strcmp(gcomprisBoard->mode, "plus") == 0)
		board_mode = MODE_PLUS;
	else
		board_mode = DEFAULT_MODE;

	gc_set_default_background(goo_canvas_get_root_item(gcomprisBoard->canvas));

	magic_hat_next_level();

	gamewon = FALSE;
	pause_board(FALSE);
  }
}
