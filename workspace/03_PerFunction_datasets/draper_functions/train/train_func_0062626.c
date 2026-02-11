IsParameterSlotReference(
  void *theEnv,
  char *pname)
  {
   if ((strncmp(pname,SELF_STRING,SELF_LEN) == 0) ?
                  (pname[SELF_LEN] == SELF_SLOT_REF) : FALSE)
     {
      PrintErrorID(theEnv,"MSGPSR",4,FALSE);
      EnvPrintRouter(theEnv,WERROR,"Illegal slot reference in parameter list.\n");
      return(TRUE);
     }
   return(FALSE);
  }
