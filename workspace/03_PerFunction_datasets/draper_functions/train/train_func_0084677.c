_basic_apply_data(E_Config_Dialog *cfd __UNUSED__, E_Config_Dialog_Data *cfdata)
{
   Eina_List *l, *ll, *lll;
   E_Manager *man;
   E_Container *con;
   E_Zone *zone;
   E_Config_Binding_Edge *bi, *bi2;
   E_Layer layer;

   _auto_apply_changes(cfdata);

   EINA_LIST_FREE(e_config->edge_bindings, bi)
     {
        e_bindings_edge_del(bi->context, bi->edge, bi->modifiers, bi->any_mod,
                            bi->action, bi->params, bi->delay);
        eina_stringshare_del(bi->action);
        eina_stringshare_del(bi->params);
        E_FREE(bi);
     }

   e_config->multiscreen_flip = cfdata->multiscreen_flip;
   EINA_LIST_FOREACH(cfdata->binding.edge, l, bi2)
     {
        bi = E_NEW(E_Config_Binding_Edge, 1);
        bi->context = bi2->context;
        bi->edge = bi2->edge;
        bi->modifiers = bi2->modifiers;
        bi->any_mod = bi2->any_mod;
        bi->delay = bi2->delay;
        bi->action =
          ((!bi2->action) || (!bi2->action[0])) ? NULL : eina_stringshare_add(bi2->action);
        bi->params =
          ((!bi2->params) || (!bi2->params[0])) ? NULL : eina_stringshare_add(bi2->params);

        e_config->edge_bindings = eina_list_append(e_config->edge_bindings, bi);
        e_bindings_edge_add(bi->context, bi->edge, bi->modifiers, bi->any_mod,
                            bi->action, bi->params, bi->delay);
     }

   if (cfdata->fullscreen_flip != e_config->fullscreen_flip)
     {
        if (cfdata->fullscreen_flip)
          layer = E_LAYER_EDGE_FULLSCREEN;
        else
          layer = E_LAYER_EDGE;

        EINA_LIST_FOREACH(e_manager_list(), l, man)
          {
             EINA_LIST_FOREACH(man->containers, ll, con)
               {
                  EINA_LIST_FOREACH(con->zones, lll, zone)
                    e_zone_edge_win_layer_set(zone, layer);
               }
          }
     }

   e_config->fullscreen_flip = cfdata->fullscreen_flip;

   e_config_save_queue();

   return 1;
}
