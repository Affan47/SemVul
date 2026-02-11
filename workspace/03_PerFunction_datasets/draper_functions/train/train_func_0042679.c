ooRunCall
   (const char* dest, char* callToken, size_t bufsiz, ooCallOptions *opts)
{
   OOStackCommand cmd;
   OOH323CallData *call;

   if(!callToken)
   {
      return OO_STKCMD_INVALIDPARAM;
   }

   if(!(call = ooFindCallByToken(callToken))) {
      return OO_STKCMD_INVALIDPARAM;
   }

   if(call->CmdChan == 0)
   {
      if(ooCreateCallCmdConnection(call) != OO_OK)
         return OO_STKCMD_CONNECTIONERR;
   }

   if(!callToken)
      return OO_STKCMD_INVALIDPARAM;


   memset(&cmd, 0, sizeof(OOStackCommand));
   cmd.type = OO_CMD_MAKECALL;
   cmd.param1 = (void*) malloc(strlen(dest)+1);
   if(!cmd.param1)
   {
      return OO_STKCMD_MEMERR;
   }
   strcpy((char*)cmd.param1, dest);
   cmd.plen1 = strlen(dest);


   cmd.param2 = (void*) malloc(strlen(callToken)+1);
   if(!cmd.param2)
   {
      free(cmd.param1);
      return OO_STKCMD_MEMERR;
   }

   strcpy((char*)cmd.param2, callToken);
   cmd.plen2 = strlen(callToken);

   if(!opts)
   {
      cmd.param3 = 0;
   }
   else {
      cmd.param3 = (void*) malloc(sizeof(ooCallOptions));
      if(!cmd.param3)
      {
         free(cmd.param1);
         free(cmd.param2);
         return OO_STKCMD_MEMERR;
      }
      memcpy((void*)cmd.param3, opts, sizeof(ooCallOptions));
      cmd.plen3 = sizeof(ooCallOptions);
   }

   if(ooWriteCallStackCommand(call, &cmd) != OO_OK)
   {
      free(cmd.param1);
      free(cmd.param2);
      if(cmd.param3) free(cmd.param3);
      return OO_STKCMD_WRITEERR;
   }


   free(cmd.param1);
   free(cmd.param2);
   if(cmd.param3) free(cmd.param3);

   return OO_STKCMD_SUCCESS;
}
