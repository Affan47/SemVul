FnCallGetValues(struct FnCall *fp,struct Rlist *finalargs)

{ char lval[CF_MAXVARSIZE],scopeid[CF_MAXVARSIZE];
  char *arrayname,match[CF_MAXVARSIZE];
  struct Scope *ptr;
  struct Rval rval;
  struct Rlist *rp,*returnlist = NULL;
  HashIterator i;
  CfAssoc *assoc;


arrayname = finalargs->item;


if (strstr(arrayname,"."))
   {
   scopeid[0] = '\0';
   sscanf(arrayname,"%127[^.].%127s",scopeid,lval);
   }
else
   {
   strcpy(lval,arrayname);
   strcpy(scopeid,CONTEXTID);
   }

if ((ptr = GetScope(scopeid)) == NULL)
   {
   CfOut(cf_verbose,"","Function getvalues was promised an array called \"%s\" in scope \"%s\" but this was not found\n",lval,scopeid);
   SetFnCallReturnStatus("getvalues",FNCALL_SUCCESS,"Array not found in scope",NULL);
   IdempAppendRScalar(&returnlist,CF_NULL_VALUE,CF_SCALAR);
   rval.item = returnlist;
   rval.rtype = CF_LIST;
   return rval;
   }

i = HashIteratorInit(ptr->hashtable);

while ((assoc = HashIteratorNext(&i)))
   {
   snprintf(match,CF_MAXVARSIZE-1,"%.127s[",lval);

   if (strncmp(match,assoc->lval,strlen(match)) == 0)
      {
      switch(assoc->rtype)
         {
         case CF_SCALAR:
            IdempAppendRScalar(&returnlist,assoc->rval,CF_SCALAR);
            break;

         case CF_LIST:
            for (rp = assoc->rval; rp != NULL; rp = rp->next)
               {
               IdempAppendRScalar(&returnlist,assoc->rval,CF_SCALAR);
               }
            break;
         }
      }
   }

if (returnlist == NULL)
   {
   IdempAppendRScalar(&returnlist,CF_NULL_VALUE,CF_SCALAR);
   }

SetFnCallReturnStatus("getindices",FNCALL_SUCCESS,NULL,NULL);
rval.item = returnlist;


rval.rtype = CF_LIST;
return rval;
}
