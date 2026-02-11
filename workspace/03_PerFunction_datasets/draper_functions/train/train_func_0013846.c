try_moving_to(int i)
{
  int c = stack_get_card(src_stack, src_n);
  for (i=0; i<8; i++)
    if (maincells[i] != src_stack)
      {
	int j = stack_count_cards(maincells[i]) - 1;
	int f = stack_get_card(maincells[i], j);
	if (SUIT(f) == SUIT(c)
	    && VALUE(c) == VALUE(f) - 1
	    && ! FACEDOWNP(c)) {
	  clear_arrows();
	  stack_move_cards(src_stack, src_n, maincells[i]);
	  while (auto_move()) ;
	  set_arrows();
	  check_for_end_of_game();
	  return 1;
	}
      }
  return 0;
}
