EnvGetcRouter(
  void *theEnv,
  char *logicalName)
  {
   struct router *currentPtr;
   int inchar;


   if (((char *) RouterData(theEnv)->FastLoadFilePtr) == logicalName)
     {
      inchar = getc(RouterData(theEnv)->FastLoadFilePtr);

      if ((inchar == '\r') || (inchar == '\n'))
        {
         if (((char *) RouterData(theEnv)->FastLoadFilePtr) == RouterData(theEnv)->LineCountRouter)
           { IncrementLineCount(theEnv); }
        }


      return(inchar);
     }


   if (RouterData(theEnv)->FastCharGetRouter == logicalName)
     {
      inchar = (unsigned char) RouterData(theEnv)->FastCharGetString[RouterData(theEnv)->FastCharGetIndex];

      RouterData(theEnv)->FastCharGetIndex++;

      if (inchar == '\0') return(EOF);

      if ((inchar == '\r') || (inchar == '\n'))
        {
         if (RouterData(theEnv)->FastCharGetRouter == RouterData(theEnv)->LineCountRouter)
           { IncrementLineCount(theEnv); }
        }


      return(inchar);
     }


   currentPtr = RouterData(theEnv)->ListOfRouters;
   while (currentPtr != NULL)
     {
      if ((currentPtr->charget != NULL) ? QueryRouter(theEnv,logicalName,currentPtr) : FALSE)
        {
         if (currentPtr->environmentAware)
           { inchar = (*currentPtr->charget)(theEnv,logicalName); }
         else
           { inchar = ((int (*)(char *)) (*currentPtr->charget))(logicalName); }

         if ((inchar == '\r') || (inchar == '\n'))
           {
            if ((RouterData(theEnv)->LineCountRouter != NULL) &&
                (strcmp(logicalName,RouterData(theEnv)->LineCountRouter) == 0))
              { IncrementLineCount(theEnv); }
           }


         return(inchar);
        }
      currentPtr = currentPtr->next;
     }


   UnrecognizedRouterMessage(theEnv,logicalName);
   return(-1);
  }
