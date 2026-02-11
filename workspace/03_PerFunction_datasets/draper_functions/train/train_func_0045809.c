SetConferenceCall(struct config_entry *p, char *Arg, AfCmd Cmd, int x)
{
   int Ret = 0;

   switch(Cmd) {
      case AF_SET_VAR:
         if(ConferenceCall != NULL) {
            free(ConferenceCall);
         }

         ConferenceCall = strdup(Arg);

         if(strcmp(ConferenceCall,"W1AW") == 0) {
            LOG_ERROR(("Come on now, your call isn't really W1AW is it!\n"));
            LOG_ERROR(("Please read the documentation, edit tbd.conf and try again.\n"));
            Ret = ERR_CONFIG_FILE;
         }
         p->Flags |= CON_FLG_SET;
         break;

      case AF_SET_DEFAULT:
         if(ConferenceCall != NULL) {
            free(ConferenceCall);
            ConferenceCall = NULL;
         }
         break;

      case AF_DISPLAY_VAR:
         strncpy(Arg,ConferenceCall,x);
         break;
   }
   return Ret;
}
