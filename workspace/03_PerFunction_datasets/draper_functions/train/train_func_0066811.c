_e_xkb_init_timer(void *data)
{
   Eina_List *l;
   E_Config_XKB_Layout *cl2, *cl = data;
   int cur_group = -1;

   EINA_LIST_FOREACH(e_config->xkb.used_layouts, l, cl2)
     {
        cur_group++;
        if (!cl2->name) continue;
        if (e_config_xkb_layout_eq(cl, cl2))
          {
             INF("Setting keyboard layout: %s|%s|%s", cl2->name, cl2->model, cl2->variant);
             e_xkb_update(cur_group);
             break;
          }
     }
   return EINA_FALSE;
}
