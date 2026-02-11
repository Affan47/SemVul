ScanString(
  void *theEnv,
  char *logicalName)
  {
   int inchar;
   int pos = 0;
   unsigned max = 0;
   char *theString = NULL;
   void *thePtr;


   inchar = EnvGetcRouter(theEnv,logicalName);
   while ((inchar != '"') && (inchar != EOF))
     {
      if (inchar == '\\')
        { inchar = EnvGetcRouter(theEnv,logicalName); }

      theString = ExpandStringWithChar(theEnv,inchar,theString,&pos,&max,max+80);
      inchar = EnvGetcRouter(theEnv,logicalName);
     }

   if ((inchar == EOF) && (ScannerData(theEnv)->IgnoreCompletionErrors == FALSE))
     { EnvPrintRouter(theEnv,WERROR,"\nEncountered End-Of-File while scanning a string\n"); }


   if (theString == NULL)
     { thePtr = EnvAddSymbol(theEnv,""); }
   else
     {
      thePtr = EnvAddSymbol(theEnv,theString);
      rm(theEnv,theString,max);
     }

   return(thePtr);
  }
