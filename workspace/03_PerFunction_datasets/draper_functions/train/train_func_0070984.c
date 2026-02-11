stack_take_card(Stack *s)
{
  int rv = -1;
  if (s->num_cards > 0)
  {
    rv = s->cards[--s->num_cards];
    stack_show_change(s, s->num_cards, s->num_cards-1);
  }
  return rv;
}
