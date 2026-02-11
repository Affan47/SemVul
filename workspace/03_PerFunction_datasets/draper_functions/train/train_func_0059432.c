_e_mod_notify_cb_resize(E_Win *win)
{
   Ind_Notify_Win *nwin;

   if (!(nwin = win->data)) return;
   if (nwin->o_base) evas_object_resize(nwin->o_base, win->w, win->h);
}
