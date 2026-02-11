enable_move (web)
     struct web *web;
{
  struct move_list *ml;
  for (ml = web->moves; ml; ml = ml->next)
    if (ml->move->type == ACTIVE)
      {
	remove_list (ml->move->dlink, &mv_active);
	put_move (ml->move, WORKLIST);
      }
}
