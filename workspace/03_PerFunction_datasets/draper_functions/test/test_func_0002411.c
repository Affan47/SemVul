_evry_selector_plugins_get(Evry_Selector *sel, Evry_Item *it, const char *plugin_name)
{
   Eina_List *l, *plugins = NULL;
   Evry_Plugin *p, *pp;
   Evry_Window *win = sel->win;
   Evry_Action *act = NULL;

   while (sel->state)
     _evry_state_pop(sel, 1);

   if ((sel != SUBJ_SEL) && (!it))
     return 0;

   if (it && CHECK_TYPE(it, EVRY_TYPE_ACTION))
     act = (Evry_Action *)it;

   EINA_LIST_FOREACH (sel->plugins, l, p)
     {
        if (!p->config->enabled && !win->plugin_dedicated)
          continue;

        if (plugin_name && strcmp(plugin_name, p->name))
          continue;

        if (act && (!CHECK_SUBTYPE(p, act->it2.type)))
          continue;

        if (p->begin && (pp = p->begin(p, it)))
          plugins = eina_list_append(plugins, pp);
     }

   _evry_state_new(sel, plugins);

   if (plugins)
     _evry_matches_update(sel, 1);

   return 1;
}
