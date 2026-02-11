IsItemIn(struct Item *list,const char *item)

{ struct Item *ptr;

if ((item == NULL) || (strlen(item) == 0))
   {
   return true;
   }

for (ptr = list; ptr != NULL; ptr=ptr->next)
   {
   if (strcmp(ptr->name,item) == 0)
      {
      return(true);
      }
   }

return(false);
}
