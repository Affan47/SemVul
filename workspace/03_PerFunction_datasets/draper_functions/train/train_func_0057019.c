FnCallHostRange(struct FnCall *fp,struct Rlist *finalargs)

{
  struct Rval rval;
  char buffer[CF_BUFSIZE];

buffer[0] = '\0';


strcpy(buffer,"!any");

if (!FuzzyHostParse(finalargs->item,finalargs->next->item))
   {
   strcpy(buffer,"!any");
   SetFnCallReturnStatus("IPRange",FNCALL_FAILURE,NULL,NULL);
   }
else if (FuzzyHostMatch(finalargs->item,finalargs->next->item,VUQNAME) == 0)
   {
   strcpy(buffer,"any");
   SetFnCallReturnStatus("IPRange",FNCALL_SUCCESS,NULL,NULL);
   }
else
   {
   strcpy(buffer,"!any");
   SetFnCallReturnStatus("IPRange",FNCALL_SUCCESS,NULL,NULL);
   }

if ((rval.item = strdup(buffer)) == NULL)
   {
   FatalError("Memory allocation in FnCallChangedBefore");
   }


rval.rtype = CF_SCALAR;
return rval;
}
