_evry_hide_func(Evry_Window *win, int finished)
{
   if ((finished) && (win->grab))
     evry_hide(win, 0);
}
