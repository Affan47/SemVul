_modify_edge_binding_cb(void *data, void *data2 __UNUSED__)
{
   E_Config_Dialog_Data *cfdata;

   cfdata = data;

   _auto_apply_changes(cfdata);

   cfdata->locals.add = 0;
   if (cfdata->locals.cur && cfdata->locals.cur[0])
     {
        E_Config_Binding_Edge *bi;
        int n;

        if (sscanf(cfdata->locals.cur, "e%d", &n) != 1)
          return;

        bi = eina_list_nth(cfdata->binding.edge, n);
        cfdata->locals.edge = bi->edge;
        cfdata->locals.delay = ((double)bi->delay);
        if (bi->delay <= -1.0) cfdata->locals.click = 1, cfdata->locals.button = -bi->delay;
        else cfdata->locals.click = 0, cfdata->locals.button = 0;
        cfdata->locals.modifiers = bi->modifiers;
     }
   else return;
   _edge_grab_wnd_show(cfdata);
}
