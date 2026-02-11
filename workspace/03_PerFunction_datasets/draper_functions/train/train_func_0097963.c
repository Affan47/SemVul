e_xkb_layout_next(void)
{
   Eina_List *l;
   E_Config_XKB_Layout *cl;

   l = eina_list_nth_list(e_config->xkb.used_layouts, e_config->xkb.cur_group);
   l = eina_list_next(l);
   if (!l) l = e_config->xkb.used_layouts;

   e_config->xkb.cur_group = (e_config->xkb.cur_group + 1) % eina_list_count(e_config->xkb.used_layouts);
   cl = eina_list_data_get(l);
   eina_stringshare_replace(&e_config->xkb.cur_layout, cl->name);
   eina_stringshare_replace(&e_config->xkb.selected_layout, cl->name);
   INF("Setting keyboard layout: %s|%s|%s", cl->name, cl->model, cl->variant);
   e_xkb_update(e_config->xkb.cur_group);
   _e_xkb_update_event(e_config->xkb.cur_group);
   e_config_save_queue();
}
