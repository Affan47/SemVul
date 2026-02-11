bots_in_subtree(tand_t *bot)
{
  int nr = 1;
  tand_t *b;

  if (!bot)
    return 0;
  for (b = tandbot; b; b = b->next) {
    if (b->bot && (b->uplink == bot)) {
      nr += bots_in_subtree(b);
    }
  }
  return nr;
}
