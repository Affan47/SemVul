_evry_items_sort_func(const void *data1, const void *data2)
{
   const Evry_Item *it1 = data1;
   const Evry_Item *it2 = data2;


   if (((it1->type == EVRY_TYPE_ACTION) || (it1->subtype == EVRY_TYPE_ACTION)) &&
       ((it2->type == EVRY_TYPE_ACTION) || (it2->subtype == EVRY_TYPE_ACTION)))
     {
        const Evry_Action *act1 = data1;
        const Evry_Action *act2 = data2;


        if (act1->it1.item && act2->it1.item)
          {
             if ((act1->it1.type == act1->it1.item->type) &&
                 (act2->it1.type != act2->it1.item->type))
               return -1;

             if ((act1->it1.type != act1->it1.item->type) &&
                 (act2->it1.type == act2->it1.item->type))
               return 1;
          }


        if (act1->remember_context)
          {
             if (!act2->remember_context)
               return -1;
          }
        else
          {
             if (act2->remember_context)
               return 1;
          }
     }


   if (_sort_flags)
     {


        if (it1->type != EVRY_TYPE_ACTION &&
            it2->type != EVRY_TYPE_ACTION)
          {
             int prio1 = it1->plugin->config->priority;
             int prio2 = it2->plugin->config->priority;

             if (prio1 - prio2)
               return prio1 - prio2;
          }
     }


   if (it1->fuzzy_match > 0 || it2->fuzzy_match > 0)
     {
        if (it2->fuzzy_match <= 0)
          return -1;

        if (it1->fuzzy_match <= 0)
          return 1;

        if (abs (it1->fuzzy_match - it2->fuzzy_match) > 5)
          return it1->fuzzy_match - it2->fuzzy_match;
     }


   if (it1->usage > 0.0 || it2->usage > 0.0)
     {
        return it1->usage > it2->usage ? -1 : 1;
     }


   if (it1->fuzzy_match > 0 || it2->fuzzy_match > 0)
     {
        if (it1->fuzzy_match - it2->fuzzy_match)
          return it1->fuzzy_match - it2->fuzzy_match;
     }


   if ((it1->plugin == it2->plugin) &&
       (it1->priority - it2->priority))
     return it1->priority - it2->priority;


   if (it1->type != EVRY_TYPE_ACTION &&
       it2->type != EVRY_TYPE_ACTION)
     {
        int prio1 = it1->plugin->config->priority;
        int prio2 = it2->plugin->config->priority;

        if (prio1 - prio2)
          return prio1 - prio2;
     }

   return strcasecmp(it1->label, it2->label);
}
