_e_shelf_cb_menu_delete(void *data, E_Menu *m __UNUSED__, E_Menu_Item *mi __UNUSED__)
{
   E_Shelf *es;

   es = data;
   if (e_config->cnfmdlg_disabled)
     {
        if (e_object_is_del(E_OBJECT(es))) return;
        es->cfg_delete = 1;
        e_object_del(E_OBJECT(es));

        e_config_save_queue();
        return;
     }

   e_object_ref(E_OBJECT(es));
   e_confirm_dialog_show(_("Are you sure you want to delete this shelf?"),
                         "enlightenment",
                         _("You requested to delete this shelf.<br>"
                           "<br>"
                           "Are you sure you want to delete it?"),
                         _("Delete"), _("Keep"),
                         _e_shelf_cb_confirm_dialog_yes, NULL, data, NULL,
                         _e_shelf_cb_confirm_dialog_destroy, data);
}
