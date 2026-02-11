_e_mod_ind_win_cb_menu_items_append(void *data, E_Gadcon_Client *gcc __UNUSED__, E_Menu *mn)
{
   Ind_Win *iwin;

   if (!(iwin = data)) return;
   _e_mod_ind_win_cb_menu_append(iwin, mn);
}
