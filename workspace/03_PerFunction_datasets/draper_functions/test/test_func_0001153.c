FnCallRegArray(struct FnCall *fp,struct Rlist *finalargs)

{ char lval[CF_MAXVARSIZE],scopeid[CF_MAXVARSIZE];
  char *regex,*arrayname,match[CF_MAXVARSIZE],buffer[CF_BUFSIZE];
  struct Scope *ptr;
  struct Rval rval;
  HashIterator i;
  CfAssoc *assoc;


arrayname = finalargs->item;
regex = finalargs->next->item;


if (strstr(arrayname,"."))
   {
   scopeid[0] = '\0';
   sscanf(arrayname,"%[^.].%s",scopeid,lval);
   }
else
   {
   strcpy(lval,arrayname);
   strcpy(scopeid,CONTEXTID);
   }

if ((ptr = GetScope(scopeid)) == NULL)
   {
   CfOut(cf_error,"","Function regarray was promised an array called \"%s\" but this was not found\n",arrayname);
   SetFnCallReturnStatus("regarray",FNCALL_FAILURE,"Array not found in scope",NULL);
   rval.item = strdup("!any");
   rval.rtype = CF_SCALAR;
   return rval;
   }

strcpy(buffer,"!any");

i = HashIteratorInit(ptr->hashtable);

while ((assoc = HashIteratorNext(&i)))
   {
   snprintf(match,CF_MAXVARSIZE,"%s[",lval);
   if (strncmp(match,assoc->lval,strlen(match)) == 0)
      {
      if (FullTextMatch(regex,assoc->rval))
         {
         strcpy(buffer,"any");
         break;
         }
      }
   }

SetFnCallReturnStatus("regarray",FNCALL_SUCCESS,NULL,NULL);

if ((rval.item = strdup(buffer)) == NULL)
   {
   FatalError("Memory allocation in FnCallRegList");
   }


rval.rtype = CF_SCALAR;
return rval;
}
