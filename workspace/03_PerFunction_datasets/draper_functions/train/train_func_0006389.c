DeinstallConstructHeader(
  void *theEnv,
  struct constructHeader *theHeader)
  {
   DecrementSymbolCount(theEnv,theHeader->name);
   if (theHeader->ppForm != NULL)
     {
      rm(theEnv,theHeader->ppForm,
         sizeof(char) * (strlen(theHeader->ppForm) + 1));
      theHeader->ppForm = NULL;
     }

   if (theHeader->usrData != NULL)
     {
      ClearUserDataList(theEnv,theHeader->usrData);
      theHeader->usrData = NULL;
     }
  }
