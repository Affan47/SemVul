_e_mod_ind_win_cb_menu_contents(void *data, E_Menu *mn __UNUSED__, E_Menu_Item *mi __UNUSED__)
{
   Ind_Win *iwin;

   if (!(iwin = data)) return;
   if (!iwin->gadcon->config_dialog)
     e_int_gadcon_config_shelf(iwin->gadcon);
   else
     {
        e_win_show(iwin->gadcon->config_dialog->dia->win);
        e_win_raise(iwin->gadcon->config_dialog->dia->win);
     }
}
