FnCallRegistryValue(struct FnCall *fp,struct Rlist *finalargs)

{
  struct Rval rval;
  char buffer[CF_BUFSIZE];

buffer[0] = '\0';


if (GetRegistryValue(finalargs->item,finalargs->next->item,buffer,sizeof(buffer)))
   {
   SetFnCallReturnStatus("registryvalue",FNCALL_SUCCESS,NULL,NULL);
   }
else
   {
   SetFnCallReturnStatus("registryvalue",FNCALL_FAILURE,NULL,NULL);
   }

if ((rval.item = strdup(buffer)) == NULL)
   {
   FatalError("Memory allocation in FnCallRegistrtValue");
   }


rval.rtype = CF_SCALAR;
return rval;
}
