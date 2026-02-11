_cb_sort(const void *data1, const void *data2)
{
   const Evry_Item *it1 = data1;
   const Evry_Item *it2 = data2;

   if (it1->usage && it2->usage)
     return it1->usage > it2->usage ? -1 : 1;
   if (it1->usage && !it2->usage)
     return -1;
   if (it2->usage && !it1->usage)
     return 1;

   if (it1->fuzzy_match || it2->fuzzy_match)
     {
        if (it1->fuzzy_match && !it2->fuzzy_match)
          return -1;

        if (!it1->fuzzy_match && it2->fuzzy_match)
          return 1;

        if (it1->fuzzy_match - it2->fuzzy_match)
          return it1->fuzzy_match - it2->fuzzy_match;
     }

   return strcasecmp(it1->label, it2->label);
}
