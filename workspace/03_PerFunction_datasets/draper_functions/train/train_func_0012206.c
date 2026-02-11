evry_util_plugin_items_add(Evry_Plugin *p, Eina_List *items, const char *input,
                           int match_detail, int set_usage)
{
   Eina_List *l;
   Evry_Item *it;
   int match = 0;

   EINA_LIST_FOREACH (items, l, it)
     {
        it->fuzzy_match = 0;

        if (set_usage)
          evry_history_item_usage_set(it, input, NULL);

        if (!input)
          {
             p->items = eina_list_append(p->items, it);
             continue;
          }

        it->fuzzy_match = evry_fuzzy_match(it->label, input);

        if (match_detail)
          {
             match = evry_fuzzy_match(it->detail, input);

             if (!(it->fuzzy_match) || (match && (match < it->fuzzy_match)))
               it->fuzzy_match = match;
          }

        if (it->fuzzy_match)
          p->items = eina_list_append(p->items, it);
     }

   p->items = eina_list_sort(p->items, -1, _evry_items_sort_func);

   return !!(p->items);
}
