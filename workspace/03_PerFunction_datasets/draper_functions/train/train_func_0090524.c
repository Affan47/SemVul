FnCallTranslatePath(struct FnCall *fp,struct Rlist *finalargs)

{
  struct Rval rval;
  char buffer[MAX_FILENAME];

buffer[0] = '\0';


snprintf(buffer, sizeof(buffer), "%s", (char *)finalargs->item);
MapName(buffer);


if ((rval.item = strdup(buffer)) == NULL)
   {
   FatalError("Memory allocation in FnCallChangedBefore");
   }

SetFnCallReturnStatus("translatepath",FNCALL_SUCCESS,NULL,NULL);


rval.rtype = CF_SCALAR;
return rval;
}
