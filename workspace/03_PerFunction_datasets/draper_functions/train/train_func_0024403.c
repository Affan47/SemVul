_fill_data(E_Config_Dialog_Data *cfdata)
{
   Eina_List *l;
   E_Config_Binding_Mouse *eb, *eb2;
   E_Config_Binding_Wheel *bw, *bw2;

   cfdata->locals.binding = eina_stringshare_add("");
   cfdata->locals.action = eina_stringshare_add("");
   cfdata->locals.params = strdup("");
   cfdata->locals.context = E_BINDING_CONTEXT_ANY;
   cfdata->binding.mouse = NULL;
   cfdata->binding.wheel = NULL;
   cfdata->locals.eg = NULL;

   EINA_LIST_FOREACH(e_config->mouse_bindings, l, eb)
     {
        eb2 = E_NEW(E_Config_Binding_Mouse, 1);
        eb2->context = eb->context;
        eb2->button = eb->button;
        eb2->modifiers = eb->modifiers;
        eb2->any_mod = eb->any_mod;
        eb2->action = !eb->action ? NULL : eina_stringshare_add(eb->action);
        eb2->params = !eb->params ? NULL : eina_stringshare_add(eb->params);

        cfdata->binding.mouse = eina_list_append(cfdata->binding.mouse, eb2);
     }

   EINA_LIST_FOREACH(e_config->wheel_bindings, l, bw)
     {
        bw2 = E_NEW(E_Config_Binding_Wheel, 1);
        bw2->context = bw->context;
        bw2->direction = bw->direction;
        bw2->z = bw->z;
        bw2->modifiers = bw->modifiers;
        bw2->any_mod = bw->any_mod;
        bw2->action = !bw->action ? NULL : eina_stringshare_add(bw->action);
        bw2->params = !bw->params ? NULL : eina_stringshare_add(bw->params);

        cfdata->binding.wheel = eina_list_append(cfdata->binding.wheel, bw2);
     }
}
