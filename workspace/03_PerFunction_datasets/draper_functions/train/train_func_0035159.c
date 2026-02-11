_add_item(Plugin *p, Plugin_Config *pc)
{
   Evry_Plugin *pp;
   Evry_Item *it = NULL;

   if (pc->enabled && (pp = evry_plugin_find(pc->name)))
     {
        pc->plugin = pp;

        GET_ITEM(itp, pp);
        it = EVRY_ITEM_NEW(Evry_Item, EVRY_PLUGIN(p), itp->label, NULL, NULL);
        if (itp->icon) it->icon = eina_stringshare_ref(itp->icon);
        it->icon_get = itp->icon_get;
        it->data = pc;
        it->browseable = EINA_TRUE;
        it->detail = eina_stringshare_ref(EVRY_ITEM(p)->label);
        p->plugins = eina_list_append(p->plugins, it);
     }
   return it;
}
