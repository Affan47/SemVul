SelectItemMatching(struct Item *start,char *regex,struct Item *begin_ptr,struct Item *end_ptr,struct Item **match,struct Item **prev,char *fl)

{ struct Item *ip;
 int ret = false;

*match = CF_UNDEFINED_ITEM;
*prev = CF_UNDEFINED_ITEM;

if (regex == NULL)
   {
   return false;
   }

if (fl && (strcmp(fl,"first") == 0))
   {
   if (SelectNextItemMatching(regex,begin_ptr,end_ptr,match,prev))
      {
      ret = true;
      }
   }
else
   {
   if (SelectLastItemMatching(regex,begin_ptr,end_ptr,match,prev))
      {
      ret = true;
      }
   }

if (*match != CF_UNDEFINED_ITEM && *prev == CF_UNDEFINED_ITEM)
   {
   for (ip = start; ip != NULL && ip != *match; ip = ip->next)
      {
      *prev = ip;
      }
   }

return ret;
}
