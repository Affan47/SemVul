_finish(Evry_Plugin *plugin)
{
   GET_PLUGIN(p, plugin);
   Ecore_Event_Handler *h;
   Evry_Item *it;
   int items = 0;

   EINA_LIST_FREE (p->base.items, it)
     {
        if ((items++ > 1) && (items < 10))
          history = eina_list_prepend(history, eina_stringshare_add(it->label));

        if (it == cur_item)
          cur_item = NULL;

        EVRY_ITEM_FREE(it);
     }

   if (cur_item)
     {
        EVRY_ITEM_FREE(cur_item);
        cur_item = NULL;
     }

   EINA_LIST_FREE (handlers, h)
     ecore_event_handler_del(h);

   if (exe)
     {
        ecore_exe_quit(exe);
        ecore_exe_free(exe);
        exe = NULL;
     }
   active = EINA_FALSE;

   E_FREE(p);
}
