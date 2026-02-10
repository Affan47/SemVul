FnCallExecResult(struct FnCall *fp,struct Rlist *finalargs)


{
  struct Rval rval;
  char buffer[CF_EXPANDSIZE];
  int ret = false;

buffer[0] = '\0';


if (!IsAbsoluteFileName(finalargs->item))
   {
   CfOut(cf_error,"","execresult \"%s\" does not have an absolute path\n",finalargs->item);
   SetFnCallReturnStatus("execresult",FNCALL_FAILURE,strerror(errno),NULL);
   strcpy(buffer,"!any");
   }

if (!IsExecutable(GetArg0(finalargs->item)))
   {
   CfOut(cf_error,"","execresult \"%s\" is assumed to be executable but isn't\n",finalargs->item);
   SetFnCallReturnStatus("execresult",FNCALL_FAILURE,strerror(errno),NULL);
   strcpy(buffer,"!any");
   }
else
   {
   if (strcmp(finalargs->next->item,"useshell") == 0)
      {
      ret = GetExecOutput(finalargs->item,buffer,true);
      }
   else
      {
      ret = GetExecOutput(finalargs->item,buffer,false);
      }

   if (ret)
      {
      SetFnCallReturnStatus("execresult",FNCALL_SUCCESS,NULL,NULL);
      }
   else
      {
      SetFnCallReturnStatus("execresult",FNCALL_FAILURE,strerror(errno),NULL);
      }
   }

if ((rval.item = strdup(buffer)) == NULL)
   {
   FatalError("Memory allocation in FnCallExecResult");
   }


rval.rtype = CF_SCALAR;
return rval;
}
