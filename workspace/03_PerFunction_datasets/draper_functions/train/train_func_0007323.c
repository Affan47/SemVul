EnvBsave(
  void *theEnv,
  char *fileName)
  {
   FILE *fp;
   struct BinaryItem *biPtr;
   char constructBuffer[CONSTRUCT_HEADER_SIZE];
   long saveExpressionCount;


   if (Bloaded(theEnv))
     {
      PrintErrorID(theEnv,"BSAVE",1,FALSE);
      EnvPrintRouter(theEnv,WERROR,
          "Cannot perform a binary save while a binary load is in effect.\n");
      return(0);
     }


   if ((fp = GenOpen(theEnv,fileName,"wb")) == NULL)
     {
      OpenErrorMessage(theEnv,"bsave",fileName);
      return(0);
     }


   SaveCurrentModule(theEnv);


   WriteBinaryHeader(theEnv,fp);


   ExpressionData(theEnv)->ExpressionCount = 0;
   InitializeFunctionNeededFlags(theEnv);
   InitAtomicValueNeededFlags(theEnv);
   FindHashedExpressions(theEnv);
   FindNeededItems(theEnv);
   SetAtomicValueIndices(theEnv,FALSE);


   WriteNeededFunctions(theEnv,fp);
   WriteNeededAtomicValues(theEnv,fp);


   GenWrite((void *) &ExpressionData(theEnv)->ExpressionCount,(unsigned long) sizeof(unsigned long),fp);


   for (biPtr = BsaveData(theEnv)->ListOfBinaryItems;
        biPtr != NULL;
        biPtr = biPtr->next)
     {
      if (biPtr->bsaveStorageFunction != NULL)
        {
         strncpy(constructBuffer,biPtr->name,CONSTRUCT_HEADER_SIZE);
         GenWrite(constructBuffer,(unsigned long) CONSTRUCT_HEADER_SIZE,fp);
         (*biPtr->bsaveStorageFunction)(theEnv,fp);
        }
     }


   WriteBinaryFooter(theEnv,fp);


   ExpressionData(theEnv)->ExpressionCount = 0;
   BsaveHashedExpressions(theEnv,fp);
   saveExpressionCount = ExpressionData(theEnv)->ExpressionCount;
   BsaveConstructExpressions(theEnv,fp);
   ExpressionData(theEnv)->ExpressionCount = saveExpressionCount;


   WriteNeededConstraints(theEnv,fp);


   for (biPtr = BsaveData(theEnv)->ListOfBinaryItems;
        biPtr != NULL;
        biPtr = biPtr->next)
     {
      if (biPtr->bsaveFunction != NULL)
        {
         strncpy(constructBuffer,biPtr->name,CONSTRUCT_HEADER_SIZE);
         GenWrite(constructBuffer,(unsigned long) CONSTRUCT_HEADER_SIZE,fp);
         (*biPtr->bsaveFunction)(theEnv,fp);
        }
     }


   WriteBinaryFooter(theEnv,fp);


   RestoreAtomicValueBuckets(theEnv);


   GenClose(theEnv,fp);


   RestoreCurrentModule(theEnv);


   return(TRUE);
  }
