SetToneSpec(struct config_entry *p, char *Arg, AfCmd Cmd, int x)
{
   char *cp;
   int ToneId;
   SavedToneSpec *pSpec = ToneSpecs;
   SavedToneSpec *pLastSpec = (SavedToneSpec *) &ToneSpecs;

   if(Cmd == AF_SET_VAR) do {
      if((cp = strstr(Arg,"ID")) == NULL && (cp = strstr(Arg,"id")) == NULL) {
         LOG_ERROR(("Error: ID not found in ToneSpec \"%s\", ignored.\n",Arg));
         break;
      }
      if(sscanf(&cp[3],"%d",&ToneId) != 1 || ToneId <= 0) {
         LOG_ERROR(("Error: invalid ID in ToneSpec \"%s\", ignored.\n",Arg));
         break;
      }

      while(pSpec != NULL) {
         if(pSpec->ID == ToneId) {

            pLastSpec->Link = pSpec->Link;
            free(pSpec);
            break;
         }
         pSpec = pSpec->Link;
      }

      pSpec = (SavedToneSpec *) malloc(sizeof(SavedToneSpec) + strlen(Arg));
      if(pSpec != NULL) {
         strcpy(pSpec->ToneSpec,Arg);
         pSpec->ID = ToneId;
         pSpec->Link = ToneSpecs;
         ToneSpecs = pSpec;
      }
   } while(FALSE);

   return 0;
}
