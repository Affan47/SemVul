e_modapi_shutdown(E_Module *m __UNUSED__)
{
   E_Config_Dialog *cfd;


   if (maug)
     {
	e_int_menus_menu_augmentation_del("config/1", maug);
	maug = NULL;
     }
   while ((cfd = e_config_dialog_get("E", "extensions/shelves")))
     e_object_del(E_OBJECT(cfd));
   e_configure_registry_item_del("extensions/shelves");
   e_configure_registry_category_del("extensions");
   conf_module = NULL;
   return 1;
}
