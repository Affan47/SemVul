auto_move()
{
  int i, something_moved = 0;
  lowest[0] = lowest[1] = 99;
  pile_for[0] = pile_for[1] = pile_for[2] = pile_for[3] = -1;
  memset(top_card, 0, sizeof(top_card));
  for (i=0; i<4; i++)
  {
    int c, n = stack_count_cards(outcells[i]);
    if (n == 0) continue;
    c = stack_get_card(outcells[i], n-1);
    top_card[i] = c;
    pile_for[SUIT(c)] = i;
    if (lowest[COLOR(c)?1:0] > VALUE(c))
      lowest[COLOR(c)?1:0] = VALUE(c);
  }
  for (i=0; i<4; i++)
    if (pile_for[i] == -1)
      lowest[COLOR(MAKE_CARD(i, ACE, FACEUP))?1:0] = 0;
  for (i=0; i<4; i++)
    something_moved += auto_move_stack(freecells[i]);
  for (i=0; i<8; i++)
    something_moved += auto_move_stack(maincells[i]);
  return something_moved;
}
