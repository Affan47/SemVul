e_int_config_interaction(E_Container *con, const char *params __UNUSED__)
{
   E_Config_Dialog *cfd;
   E_Config_Dialog_View *v;

   if (e_config_dialog_find("E", "keyboard_and_mouse/interaction"))
     return NULL;
   v = E_NEW(E_Config_Dialog_View, 1);

   v->create_cfdata = _create_data;
   v->free_cfdata = _free_data;
   v->basic.apply_cfdata = _basic_apply;
   v->basic.create_widgets = _basic_create;
   v->basic.check_changed = _basic_check_changed;
   v->override_auto_apply = 1;

   cfd = e_config_dialog_new(con, _("Interaction Settings"),
			     "E", "keyboard_and_mouse/interaction",
			     "preferences-interaction", 0, v, NULL);
   return cfd;
}
