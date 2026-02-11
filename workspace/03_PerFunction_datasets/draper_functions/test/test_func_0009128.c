_e_fm2_add_menu_pre(void *data, E_Menu *subm)
{
   E_Menu_Item *mi;
   E_Fm2_Smart_Data *sd;

   sd = data;
   if (subm->items) return;

   mi = e_menu_item_new(subm);
   e_menu_item_label_set(mi, _("Directory"));
   e_util_menu_item_theme_icon_set(mi, "folder-new");
   e_menu_item_callback_set(mi, _e_fm2_new_directory, sd);

   mi = e_menu_item_new(subm);
   e_menu_item_label_set(mi, _("File"));
   e_util_menu_item_theme_icon_set(mi, "document-new");
   e_menu_item_callback_set(mi, _e_fm2_new_file, sd);
}
