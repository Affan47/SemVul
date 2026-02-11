_ibar_cb_menu_icon_add(void *data __UNUSED__, E_Menu *m __UNUSED__, E_Menu_Item *mi __UNUSED__)
{
   E_Container *con;

   if (!e_configure_registry_exists("applications/ibar_applications")) return;
   con = e_container_current_get(e_manager_current_get());
   e_configure_registry_call("applications/ibar_applications", con, NULL);
}
