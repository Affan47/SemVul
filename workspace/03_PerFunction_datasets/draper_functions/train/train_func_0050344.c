FnCallIPRange(struct FnCall *fp,struct Rlist *finalargs)

{
  struct Rval rval;
  char buffer[CF_BUFSIZE];
  struct Item *ip;

buffer[0] = '\0';


strcpy(buffer,"!any");

if (!FuzzyMatchParse(finalargs->item))
   {
   strcpy(buffer,"!any");
   SetFnCallReturnStatus("IPRange",FNCALL_FAILURE,NULL,NULL);
   }
else
   {
   SetFnCallReturnStatus("IPRange",FNCALL_SUCCESS,NULL,NULL);

   for (ip = IPADDRESSES; ip != NULL; ip = ip->next)
      {
      Debug("Checking IP Range against RDNS %s\n",VIPADDRESS);

      if (FuzzySetMatch(finalargs->item,VIPADDRESS) == 0)
         {
         Debug("IPRange Matched\n");
         strcpy(buffer,"any");
         break;
         }
      else
         {
         Debug("Checking IP Range against iface %s\n",ip->name);

         if (FuzzySetMatch(finalargs->item,ip->name) == 0)
            {
            Debug("IPRange Matched\n");
            strcpy(buffer,"any");
            break;
            }
         }
      }
   }

if ((rval.item = strdup(buffer)) == NULL)
   {
   FatalError("Memory allocation in FnCallChangedBefore");
   }


rval.rtype = CF_SCALAR;
return rval;
}
