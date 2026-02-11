setArgusRemoteFilter(unsigned char *str)
{
   int retn = 0, len, i;
   struct ARGUS_INPUT *input = NULL;
   char buf[MAXSTRLEN];

   if (str != NULL) {
      if (ArgusRemoteFilter != str) {
         if (ArgusRemoteFilter != NULL)
            free(ArgusRemoteFilter);

         ArgusRemoteFilter = str;
      }

      for (i = 0; i < ARGUS_MAX_REMOTE_CONN; i++) {
         if ((input = ArgusRemoteFDs[i]) != NULL) {
            if ((input->status & ARGUS_DATA_SOURCE) && (input->filename == NULL)) {
               bzero(buf, MAXSTRLEN);
               snprintf ((char *) buf, MAXSTRLEN-1, "FILTER: man or (%s)", (char *) ArgusRemoteFilter);
               len = strlen((char *) buf);
               if (ArgusWriteConnection (input, (unsigned char *) buf, len) < 0) {
                  ArgusLog (LOG_ALERT, "%s: write remote filter error %s.", strerror(errno));
               }
            }
         }
      }
   }

#ifdef ARGUSDEBUG
   ArgusDebug (1, "setArgusRemoteFilter(%s) returning %d\n", str, retn);
#endif

   return (retn);
}
