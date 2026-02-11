_e_mod_ind_win_cb_min_size_request(void *data, E_Gadcon *gc, Evas_Coord w __UNUSED__, Evas_Coord h)
{
   Ind_Win *iwin;

   if (!(iwin = data)) return;
   if (gc != iwin->gadcon) return;
   if (h < iwin->win->h) h = iwin->win->h;

}
