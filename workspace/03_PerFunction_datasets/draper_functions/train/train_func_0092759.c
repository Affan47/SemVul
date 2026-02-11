_begin(Evry_Plugin *plugin, const Evry_Item *it)
{
   Evry_Action *act;
   Eina_List *l;
   Plugin *p;

   EVRY_PLUGIN_INSTANCE(p, plugin);

   if (!(CHECK_TYPE(it, EVRY_TYPE_PLUGIN)))
     {
        EINA_LIST_FOREACH (evry_conf->actions, l, act)
          {
             if (!((!act->it1.type) ||
                   (CHECK_TYPE(it, act->it1.type)) ||
                   (CHECK_SUBTYPE(it, act->it1.type))))
               continue;

             if (act->check_item && !(act->check_item(act, it)))
               continue;

             act->base.plugin = EVRY_PLUGIN(p);
             act->it1.item = it;
             EVRY_ITEM(act)->hi = NULL;

             p->actions = eina_list_append(p->actions, act);
          }
     }

   if (it->plugin)
     {
        EINA_LIST_FOREACH (it->plugin->actions, l, act)
          {
             act->base.plugin = EVRY_PLUGIN(p);

             act->it1.item = EVRY_ITEM(it->plugin);
             EVRY_ITEM(act)->hi = NULL;
             p->actions = eina_list_append(p->actions, act);
          }
     }

   return EVRY_PLUGIN(p);
}
