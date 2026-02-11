FnCallEscape(struct FnCall *fp,struct Rlist *finalargs)

{
  struct Rval rval;
  char buffer[CF_BUFSIZE];
  char *name;

buffer[0] = '\0';


name = finalargs->item;

EscapeSpecialChars(name,buffer,CF_BUFSIZE-1,"");

if ((rval.item = strdup(buffer)) == NULL)
   {
   FatalError("Memory allocation in FnCallEscape");
   }

SetFnCallReturnStatus("escape",FNCALL_SUCCESS,NULL,NULL);


rval.rtype = CF_SCALAR;
return rval;
}
