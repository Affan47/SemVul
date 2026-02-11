e_modapi_shutdown(E_Module *m __UNUSED__)
{
   E_Config_Dialog *cfd;
   while ((cfd = e_config_dialog_get("E", "menus/menu_settings"))) e_object_del(E_OBJECT(cfd));
   e_configure_registry_item_del("menus/menu_settings");
   e_configure_registry_category_del("menus");
   conf_module = NULL;
   return 1;
}
