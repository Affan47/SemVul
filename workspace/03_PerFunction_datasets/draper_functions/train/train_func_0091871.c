OutputProfileInfo(
  void *theEnv,
  char *itemName,
  struct constructProfileInfo *profileInfo,
  char *printPrefixBefore,
  char *printPrefix,
  char *printPrefixAfter,
  char **banner)
  {
   double percent = 0.0, percentWithKids = 0.0;
   char buffer[512];

   if (profileInfo == NULL) return(FALSE);

   if (profileInfo->numberOfEntries == 0) return(FALSE);

   if (ProfileFunctionData(theEnv)->ProfileTotalTime != 0.0)
     {
      percent = (profileInfo->totalSelfTime * 100.0) / ProfileFunctionData(theEnv)->ProfileTotalTime;
      if (percent < 0.005) percent = 0.0;
      percentWithKids = (profileInfo->totalWithChildrenTime * 100.0) / ProfileFunctionData(theEnv)->ProfileTotalTime;
      if (percentWithKids < 0.005) percentWithKids = 0.0;
     }

   if (percent < ProfileFunctionData(theEnv)->PercentThreshold) return(FALSE);

   if ((banner != NULL) && (*banner != NULL))
     {
      EnvPrintRouter(theEnv,WDISPLAY,*banner);
      *banner = NULL;
     }

   if (printPrefixBefore != NULL)
     { EnvPrintRouter(theEnv,WDISPLAY,printPrefixBefore); }

   if (printPrefix != NULL)
     { EnvPrintRouter(theEnv,WDISPLAY,printPrefix); }

   if (printPrefixAfter != NULL)
     { EnvPrintRouter(theEnv,WDISPLAY,printPrefixAfter); }

   if (strlen(itemName) >= 40)
     {
      EnvPrintRouter(theEnv,WDISPLAY,itemName);
      EnvPrintRouter(theEnv,WDISPLAY,"\n");
      itemName = "";
     }

   sprintf(buffer,ProfileFunctionData(theEnv)->OutputString,
                        itemName,
                        (long) profileInfo->numberOfEntries,

                        (double) profileInfo->totalSelfTime,
                        (double) percent,

                        (double) profileInfo->totalWithChildrenTime,
                        (double) percentWithKids);
   EnvPrintRouter(theEnv,WDISPLAY,buffer);

   return(TRUE);
  }
