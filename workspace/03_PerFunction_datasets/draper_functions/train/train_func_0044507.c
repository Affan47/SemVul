DeleteUserData(
  void *theEnv,
  unsigned char userDataID,
  struct userData *theList)
  {
   struct userData *theData, *lastData = NULL;

   for (theData = theList;
        theData != NULL;
        theData = theData->next)
     {
      if (theData->dataID == userDataID)
        {
         if (lastData == NULL)
           { theList = theData->next; }
         else
           { lastData->next = theData->next; }

         (*UserDataData(theEnv)->UserDataRecordArray[userDataID]->deleteUserData)(theEnv,theData);
         return(theList);
        }

      lastData = theData;
     }

   return(theList);
  }
