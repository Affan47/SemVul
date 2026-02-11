e_win_placed_set(E_Win *win, int placed)
{
   E_OBJECT_CHECK(win);
   E_OBJECT_TYPE_CHECK(win, E_WIN_TYPE);
   win->placed = placed;
   if (win->border)
     _e_win_prop_update(win);
}
