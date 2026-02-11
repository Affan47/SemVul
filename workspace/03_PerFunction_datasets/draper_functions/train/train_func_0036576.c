EnvBatchStar(
  void *theEnv,
  char *fileName)
  {
   int inchar;
   FILE *theFile;
   char *theString = NULL;
   int position = 0;
   unsigned maxChars = 0;


   theFile = GenOpen(theEnv,fileName,"r");

   if (theFile == NULL)
     {
      OpenErrorMessage(theEnv,"batch",fileName);
      return(FALSE);
     }


   SetHaltExecution(theEnv,FALSE);
   SetEvaluationError(theEnv,FALSE);


   while ((inchar = getc(theFile)) != EOF)
     {
      theString = ExpandStringWithChar(theEnv,inchar,theString,&position,
                                       &maxChars,maxChars+80);

      if (CompleteCommand(theString) != 0)
        {
         FlushPPBuffer(theEnv);
         SetPPBufferStatus(theEnv,OFF);
         RouteCommand(theEnv,theString,FALSE);
         FlushPPBuffer(theEnv);
         SetHaltExecution(theEnv,FALSE);
         SetEvaluationError(theEnv,FALSE);
         FlushBindList(theEnv);
         genfree(theEnv,theString,(unsigned) maxChars);
         theString = NULL;
         maxChars = 0;
         position = 0;
        }
     }

   if (theString != NULL)
     { genfree(theEnv,theString,(unsigned) maxChars); }


   GenClose(theEnv,theFile);
   return(TRUE);
  }
