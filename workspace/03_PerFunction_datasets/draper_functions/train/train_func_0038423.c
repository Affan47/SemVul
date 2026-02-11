ShowAllReservedWords()

{ int i,j,k,l;
 struct Item *ip,*list = NULL;
  struct SubTypeSyntax *ss;
  struct BodySyntax *bs,*bs2;

for (i = 0; CF_ALL_BODIES[i].subtype != NULL; i++)
   {
   IdempPrependItem(&list,CF_ALL_BODIES[i].subtype,NULL);

   bs = CF_ALL_BODIES[i].bs;

   for (l = 0; bs[l].lval != NULL; l++)
      {
      IdempPrependItem(&list,bs[l].lval,NULL);
      }
   }


for  (i = 0; i < CF3_MODULES; i++)
   {
   if ((ss = CF_ALL_SUBTYPES[i]) == NULL)
      {
      continue;
      }

   for (j = 0; ss[j].subtype != NULL; j++)
      {
      if ((bs = ss[j].bs) == NULL)
         {
         continue;
         }

      IdempPrependItem(&list,ss[j].subtype,NULL);

      for (l = 0; bs[l].range != NULL; l++)
         {
         if (bs[l].dtype == cf_body)
            {
            bs2 = (struct BodySyntax *)(bs[l].range);

            if (bs2 == NULL || bs2 == (void *)CF_BUNDLE)
               {
               continue;
               }

            for (k = 0; bs2[k].dtype != cf_notype; k++)
               {


               IdempPrependItem(&list,bs2[k].lval,NULL);
               }
            }
         }
      }
   }

for (ip = list; ip != NULL; ip=ip->next)
   {
   printf(" \"%s\",",ip->name);
   }

DeleteItemList(list);
}
