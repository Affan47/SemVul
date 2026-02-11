click(int x, int y, int b)
{
  int c, f;

  Picture *cp = get_centered_pic();
  src_stack = 0;


  if (drag_active) {
    stack_drop(dest_stack, last_n);
    drag_active = 0;
    return;
  };

  if ((cp == youlose || cp == youwin)
      && (x > table_width/2-cp->w/2
	  && x < table_width/2+cp->w/2
	  && y > table_height/2-cp->h/2
	  && y < table_height/2+cp->h/2))
  {
    set_centered_pic(0);
    start_again();
    return;
  }

  if (cp == splash)
  {
    set_centered_pic(0);
    return;
  }
  f = stack_find(x, y, &src_stack, &src_n);
  if (!f)
    return;

  if (b > 1)
  {
    if (src_stack && src_n>=0 && src_n <= stack_count_cards(src_stack)-1)
      stack_peek_card(src_stack, src_n, 1);
    return;
  }

  last_n = -1;

  if (src_stack == deck)
  {
    if (stack_count_cards(deck) == 0)
    {
      if (vegas)
      {
        vegas_deck_count++;
        if (vegas_deck_count >= 3)
	{
          start_again();
	  return;
	}
      }
      stack_flip_stack(hole, deck);
    }
    else
    {
      stack_flip_card(deck, hole);
      if (flip_3s)
        for (c=0; c<2; c++)
          if (stack_count_cards(deck) != 0)
	    stack_flip_card(deck, hole);
      if (vegas && vegas_deck_count == 2 && stack_count_cards(deck) == 0)
      {
        display_vegas_xlogo = 1;
        invalidate (vegas_xlogo_x, vegas_xlogo_y,
                    xlogo->w, xlogo->h);
      }
    }
    return;
  }

  if (vegas)
    for (c=0; c<4; c++)
      if (src_stack == outcells[c])
      {
        winnings -= 5;
	update_status_text(1);
      }

  if (src_n>=0 && stack_count_cards(src_stack) > 0)
  {
    c = stack_get_card(src_stack, src_n);
    if (FACEDOWNP(c))
      stack_flip_card(src_stack, src_stack);

    stack_begin_drag(src_stack, src_n, x, y);
  }
}
