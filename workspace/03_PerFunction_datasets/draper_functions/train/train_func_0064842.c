il_kbd_config_init(E_Module *m)
{
   char buff[PATH_MAX];

   conf_edd = E_CONFIG_DD_NEW("Illume_Kbd_Cfg", Il_Kbd_Config);
   #undef T
   #undef D
   #define T Il_Kbd_Config
   #define D conf_edd
   E_CONFIG_VAL(D, T, version, INT);
   E_CONFIG_VAL(D, T, use_internal, INT);
   E_CONFIG_VAL(D, T, run_keyboard, STR);
   E_CONFIG_VAL(D, T, dict, STR);
   E_CONFIG_VAL(D, T, zoom_level, INT);
   E_CONFIG_VAL(D, T, hold_timer, DOUBLE);
   E_CONFIG_VAL(D, T, slide_dim, INT);
   E_CONFIG_VAL(D, T, scale_height, DOUBLE);
   E_CONFIG_VAL(D, T, layout, INT);
   il_kbd_cfg = e_config_domain_load("module.illume-keyboard", conf_edd);
   if ((il_kbd_cfg) &&
       ((il_kbd_cfg->version >> 16) < IL_CONFIG_MAJ))
     {
        E_FREE(il_kbd_cfg);
        il_kbd_cfg = NULL;
     }
   if (!il_kbd_cfg)
     {
        il_kbd_cfg = E_NEW(Il_Kbd_Config, 1);
        il_kbd_cfg->version = 0;
        il_kbd_cfg->use_internal = 1;
        il_kbd_cfg->run_keyboard = NULL;
        il_kbd_cfg->dict = eina_stringshare_add("English_US.dic");
        il_kbd_cfg->zoom_level = 4;
        il_kbd_cfg->slide_dim = 4;
        il_kbd_cfg->hold_timer = 0.25;
     }
   if (il_kbd_cfg)
     {


        if ((il_kbd_cfg->version & 0xffff) < 2)
          {
             il_kbd_cfg->zoom_level = 4;
             il_kbd_cfg->slide_dim = 4;
             il_kbd_cfg->hold_timer = 0.25;
             il_kbd_cfg->scale_height = 1.0;
          }
        if ((il_kbd_cfg->version & 0xffff) < IL_CONFIG_MIN)
          {
             il_kbd_cfg->layout = E_KBD_INT_TYPE_ALPHA;
          }

        il_kbd_cfg->version = (IL_CONFIG_MAJ << 16) | IL_CONFIG_MIN;
     }

   il_kbd_cfg->mod_dir = eina_stringshare_add(m->dir);

   snprintf(buff, sizeof(buff), "%s/e-module-illume-keyboard.edj",
            il_kbd_cfg->mod_dir);
   e_configure_registry_category_add("illume", 0, _("Illume"), NULL,
                                     "enlightenment/display");
   e_configure_registry_generic_item_add("illume/keyboard", 0, _("Keyboard"),
                                         buff, "icon", il_kbd_config_show);
   return 1;
}
