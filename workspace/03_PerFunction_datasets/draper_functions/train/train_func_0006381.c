_fill_data(E_Config_Dialog_Data *cfdata)
{
   E_Config_Binding_Edge *bi, *bi2;
   Eina_List *l;

   cfdata->locals.params = strdup("");
   cfdata->locals.action = eina_stringshare_add("");
   cfdata->locals.binding = eina_stringshare_add("");
   cfdata->locals.cur = NULL;
   cfdata->locals.dia = NULL;
   cfdata->locals.delay = 0.3;
   cfdata->locals.click = 0;
   cfdata->binding.edge = NULL;

   EINA_LIST_FOREACH(e_config->edge_bindings, l, bi)
     {
        if (!bi) continue;

        bi2 = E_NEW(E_Config_Binding_Edge, 1);
        bi2->context = bi->context;
        bi2->edge = bi->edge;
        bi2->modifiers = bi->modifiers;
        bi2->any_mod = bi->any_mod;
        bi2->delay = bi->delay;
        bi2->action = eina_stringshare_ref(bi->action);
        bi2->params = eina_stringshare_ref(bi->params);

        cfdata->binding.edge = eina_list_append(cfdata->binding.edge, bi2);
     }

   cfdata->fullscreen_flip = e_config->fullscreen_flip;
   cfdata->multiscreen_flip = e_config->multiscreen_flip;
}
