AddEnvironmentCleanupFunction(
  void *vtheEnv,
  char *name,
  void (*functionPtr)(void *),
  int priority)
  {
   struct environmentCleanupFunction *newPtr, *currentPtr, *lastPtr = NULL;
   struct environmentData *theEnv = (struct environmentData *) vtheEnv;

   newPtr = (struct environmentCleanupFunction *) malloc(sizeof(struct environmentCleanupFunction));
   if (newPtr == NULL)
     { return(FALSE); }

   newPtr->name = name;
   newPtr->func = functionPtr;
   newPtr->priority = priority;

   if (theEnv->listOfCleanupEnvironmentFunctions == NULL)
     {
      newPtr->next = NULL;
      theEnv->listOfCleanupEnvironmentFunctions = newPtr;
      return(TRUE);
     }

   currentPtr = theEnv->listOfCleanupEnvironmentFunctions;
   while ((currentPtr != NULL) ? (priority < currentPtr->priority) : FALSE)
     {
      lastPtr = currentPtr;
      currentPtr = currentPtr->next;
     }

   if (lastPtr == NULL)
     {
      newPtr->next = theEnv->listOfCleanupEnvironmentFunctions;
      theEnv->listOfCleanupEnvironmentFunctions = newPtr;
     }
   else
     {
      newPtr->next = currentPtr;
      lastPtr->next = newPtr;
     }

   return(TRUE);
  }
