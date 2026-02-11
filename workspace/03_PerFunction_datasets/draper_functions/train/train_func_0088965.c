get_next_selection (GList * selection, GList ** list, int *curnum)
{
  gftp_file * tempfle;
  int i, newpos;

  newpos = GPOINTER_TO_INT (selection->data);
  i = *curnum - newpos;

  if (i < 0)
    {
      while (i != 0)
        {
          tempfle = (*list)->data;
          if (tempfle->shown)
            {
	      ++*curnum;
	      i++;
            }
	  *list = (*list)->next;
        }
    }
  else if (i > 0)
    {
      while (i != 0)
        {
          tempfle = (*list)->data;
          if (tempfle->shown)
            {
	      --*curnum;
	      i--;
            }
	  *list = (*list)->prev;
        }
    }

  tempfle = (*list)->data;
  while ((*list)->next && !tempfle->shown)
    {
      *list = (*list)->next;
      tempfle = (*list)->data;
    }
  return (selection->next);
}
