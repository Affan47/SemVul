ooCallAddAlias
   (OOH323CallData *call, int aliasType, const char *value, OOBOOL local)
{
   ooAliases * psNewAlias=NULL;
   psNewAlias = (ooAliases*)memAlloc(call->pctxt, sizeof(ooAliases));
   if(!psNewAlias)
   {
      OOTRACEERR3("Error:Memory - ooCallAddAlias - psNewAlias"
                  "(%s, %s)\n", call->callType, call->callToken);
      return OO_FAILED;
   }
   psNewAlias->type = aliasType;
   psNewAlias->value = (char*) memAlloc(call->pctxt, strlen(value)+1);
   if(!psNewAlias->value)
   {
      OOTRACEERR3("Error:Memory - ooCallAddAlias - psNewAlias->value"
                  " (%s, %s)\n", call->callType, call->callToken);
      memFreePtr(call->pctxt, psNewAlias);
      return OO_FAILED;
   }
   strcpy(psNewAlias->value, value);

   if(local)
   {
      psNewAlias->next = call->ourAliases;
      call->ourAliases = psNewAlias;
   }
   else {
     psNewAlias->next = call->remoteAliases;
     call->remoteAliases = psNewAlias;
   }

   OOTRACEDBGC5("Added %s alias %s to call. (%s, %s)\n",
              local?"local":"remote", value, call->callType, call->callToken);
   return OO_OK;
}
