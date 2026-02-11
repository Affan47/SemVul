EnvDeleteRouter(
  void *theEnv,
  char *routerName)
  {
   struct router *currentPtr, *lastPtr;

   currentPtr = RouterData(theEnv)->ListOfRouters;
   lastPtr = NULL;

   while (currentPtr != NULL)
     {
      if (strcmp(currentPtr->name,routerName) == 0)
        {
         if (lastPtr == NULL)
           {
            RouterData(theEnv)->ListOfRouters = currentPtr->next;
            rm(theEnv,currentPtr,(int) sizeof(struct router));
            return(1);
           }
         lastPtr->next = currentPtr->next;
         rm(theEnv,currentPtr,(int) sizeof(struct router));
         return(1);
        }
      lastPtr = currentPtr;
      currentPtr = currentPtr->next;
     }

   return(0);
  }
