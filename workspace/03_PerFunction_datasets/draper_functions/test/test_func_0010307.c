FnCallGetIndices(struct FnCall *fp,struct Rlist *finalargs)

{ char lval[CF_MAXVARSIZE],scopeid[CF_MAXVARSIZE];
  char *arrayname,index[CF_MAXVARSIZE],match[CF_MAXVARSIZE];
  struct Scope *ptr;
  struct Rval rval;
  struct Rlist *returnlist = NULL;
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
   CfOut(cf_verbose,"","Function getindices was promised an array called \"%s\" in scope \"%s\" but this was not found\n",lval,scopeid);
   SetFnCallReturnStatus("getindices",FNCALL_SUCCESS,"Array not found in scope",NULL);
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
      char *sp;
      index[0] = '\0';
      sscanf(assoc->lval+strlen(match),"%127[^\n]",index);
      if ((sp = strchr(index,']')))
         {
         *sp = '\0';
         }
      else
         {
         index[strlen(index)-1] = '\0';
         }

      if (strlen(index) > 0)
         {
         IdempAppendRScalar(&returnlist,index,CF_SCALAR);
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
