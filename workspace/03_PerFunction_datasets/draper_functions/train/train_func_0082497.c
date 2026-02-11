_e_toolbar_menu_cb_edit(void *data, E_Menu *mn __UNUSED__, E_Menu_Item *mi __UNUSED__)
{
   E_Toolbar *tbar;

   tbar = data;
   if (tbar->gadcon->editing)
     e_gadcon_edit_end(tbar->gadcon);
   else
     e_gadcon_edit_begin(tbar->gadcon);
}
