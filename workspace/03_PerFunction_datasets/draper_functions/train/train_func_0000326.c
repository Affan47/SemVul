list_deiconify(unsigned long *body)
{
  PagerWindow *t;
  Window target_w;

  target_w = body[0];
  t = Start;
  while((t!= NULL)&&(t->w != target_w))
    {
      t = t->next;
    }
  if(t== NULL)
    {
      return;
    }
  else
    {
      t->flags &= ~ICONIFIED;
      t->x = t->frame_x;
      t->y = t->frame_y;
      t->width = t->frame_width;
      t->height = t->frame_height;
      MoveResizePagerView(t);
      if(FocusWin == t)
	Hilight(t,ON);
      else
	Hilight(t,OFF);
    }
}
