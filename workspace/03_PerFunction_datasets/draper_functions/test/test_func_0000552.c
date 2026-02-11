e_modapi_init(E_Module *m)
{

   if (!ecore_con_url_init())
     {
        e_util_dialog_show(_("Shot Error"),
                           _("Cannot initialize network"));
        return NULL;
     }

   e_module_delayed_set(m, 1);

   shot_module = m;
   act = e_action_add("shot");
   if (act)
     {
        act->func.go = _e_mod_action_cb;
        e_action_predef_name_set(N_("Screen"), N_("Take Screenshot"),
                                 "shot", NULL, NULL, 0);
     }
   border_act = e_action_add("border_shot");
   if (border_act)
     {
        border_act->func.go = _e_mod_action_border_cb;
        e_action_predef_name_set(N_("Window : Actions"), N_("Take Shot"),
                                 "border_shot", NULL, NULL, 0);
     }
   maug = e_int_menus_menu_augmentation_add_sorted
      ("main/2",  _("Take Screenshot"), _e_mod_menu_add, NULL, NULL, NULL);
   border_hook = e_int_border_menu_hook_add(_bd_hook, NULL);
   return m;
}
