e_int_config_borders_border(E_Container *con __UNUSED__, const char *params)
{
   E_Config_Dialog *cfd;
   E_Config_Dialog_View *v;
   E_Border *bd;

   if (!params) return NULL;
   bd = NULL;
   sscanf(params, "%p", &bd);
   if (!bd) return NULL;
   v = _config_view_new();
   if (!v) return NULL;
   cfd = e_config_dialog_new(bd->zone->container,
                             _("Window Border Selection"),
                             "E", "_config_border_border_style_dialog",
                             "preferences-system-windows", 0, v, bd);
   bd->border_border_dialog = cfd;
   return cfd;
}
