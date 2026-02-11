e_mod_illume_config_animation_show(E_Container *con, const char *params __UNUSED__)
{
   E_Config_Dialog *cfd;
   E_Config_Dialog_View *v;

   if (e_config_dialog_find("E", "illume/animation")) return;

   v = E_NEW(E_Config_Dialog_View, 1);
   if (!v) return;

   v->create_cfdata = _e_mod_illume_config_animation_create;
   v->free_cfdata = _e_mod_illume_config_animation_free;
   v->basic.create_widgets = _e_mod_illume_config_animation_ui;
   v->basic_only = 1;
   v->normal_win = 1;
   v->scroll = 1;

   cfd = e_config_dialog_new(con, _("Animation Settings"), "E",
                             "illume/animation",
                             "enlightenment/animation_settings", 0, v, NULL);
   if (!cfd) return;

}
