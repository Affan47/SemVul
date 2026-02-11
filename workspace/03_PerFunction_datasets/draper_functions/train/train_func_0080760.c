_create_data(E_Config_Dialog *cfd __UNUSED__)
{
   E_Config_Dialog_Data *cfdata;
   Eina_List *l, *ll, *lll;
   E_Config_XKB_Layout *cl, *nl;
   E_XKB_Dialog_Option *od;
   E_XKB_Option *op;
   E_XKB_Option_Group *gr;

   find_rules();
   parse_rules();

   cfdata = E_NEW(E_Config_Dialog_Data, 1);

   cfdata->cfg_layouts = NULL;
   EINA_LIST_FOREACH(e_config->xkb.used_layouts, l, cl)
     {
        nl = E_NEW(E_Config_XKB_Layout, 1);
        nl->name = eina_stringshare_add(cl->name);
        nl->model = eina_stringshare_add(cl->model);
        nl->variant = eina_stringshare_add(cl->variant);

        cfdata->cfg_layouts = eina_list_append(cfdata->cfg_layouts, nl);
     }


   cfdata->only_label = e_config->xkb.only_label;
   cfdata->cfg_options = NULL;

   lll = e_config->xkb.used_options;
   EINA_LIST_FOREACH(optgroups, l, gr)
     {
        EINA_LIST_FOREACH(gr->options, ll, op)
          {
             od = E_NEW(E_XKB_Dialog_Option, 1);
             od->name = eina_stringshare_add(op->name);
             if (lll &&
                 (od->name == ((E_Config_XKB_Option *)
                               eina_list_data_get(lll))->name))
               {
                  od->enabled = 1;
                  lll = eina_list_next(lll);
               }
             else od->enabled = 0;
             cfdata->cfg_options = eina_list_append(cfdata->cfg_options, od);
          }
     }

   return cfdata;
}
