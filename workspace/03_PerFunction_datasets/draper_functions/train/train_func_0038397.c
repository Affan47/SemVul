_e_mod_ind_win_cb_menu_post(void *data, E_Menu *mn __UNUSED__)
{
   Ind_Win *iwin;

   if (!(iwin = data)) return;
   if (!iwin->menu) return;
   e_object_del(E_OBJECT(iwin->menu));
   iwin->menu = NULL;
}
