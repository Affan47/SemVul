ArgusConvertInitialWriteStruct (struct WriteStruct *ws, struct ArgusRecord *argus)
{
   int retn = 0;
   char *ptr;

   if (ws && argus) {
      bzero ((char *) argus, sizeof (*argus));
      if ((ptr = strstr (ws->ws_init.initString, ArgusVersionStr)) != NULL) {
         ptr = &ptr[strlen(ArgusVersionStr)];
         if (sscanf (ptr, "%d.%d", &major_version, &minor_version)) {
            argus->ahdr.type                 = ARGUS_MAR | ARGUS_WRITESTRUCT;
            argus->ahdr.length               = sizeof (*argus);
            argus->ahdr.length               = htons(argus->ahdr.length);
            argus->ahdr.cause                = ARGUS_START;
            argus->ahdr.status               = htonl(ARGUS_VERSION);
            argus->ahdr.argusid              = htonl(ARGUS_COOKIE);
            argus->argus_mar.startime        = ws->ws_init.startime;
            argus->argus_mar.now             = ws->ws_init.now;
            argus->argus_mar.major_version   = major_version;
            argus->argus_mar.minor_version   = minor_version;
            argus->argus_mar.interfaceType   = ws->ws_init.interfaceType;
            argus->argus_mar.interfaceStatus = ws->ws_init.interfaceStatus;

            argus->argus_mar.reportInterval  = ws->ws_init.reportInterval;
            argus->argus_mar.argusMrInterval = ws->ws_init.dflagInterval;
            argus->argus_mar.record_len      = -1;
            retn = 1;
         }
      }
   }

   return (retn);
}
