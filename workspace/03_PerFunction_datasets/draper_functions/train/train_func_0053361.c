LvalWantsBody(char *stype,char *lval)

{
  int i,j,l;
  struct SubTypeSyntax *ss;
  struct BodySyntax *bs;

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

      if (strcmp(ss[j].subtype,stype) != 0)
         {
         continue;
         }

      for (l = 0; bs[l].range != NULL; l++)
         {
         if (strcmp(bs[l].lval,lval) == 0)
            {
            if (bs[l].dtype == cf_body)
               {
               return true;
               }
            else
               {
               return false;
               }
            }
         }
      }
   }

return false;
}
