WriteNeededSymbols(
  void *theEnv,
  FILE *fp)
  {
   unsigned long i;
   unsigned length;
   SYMBOL_HN **symbolArray;
   SYMBOL_HN *symbolPtr;
   unsigned long int numberOfUsedSymbols = 0, size = 0;


   symbolArray = GetSymbolTable(theEnv);


   for (i = 0; i < SYMBOL_HASH_SIZE; i++)
     {
      for (symbolPtr = symbolArray[i];
           symbolPtr != NULL;
           symbolPtr = symbolPtr->next)
        {
         if (symbolPtr->neededSymbol)
           {
            numberOfUsedSymbols++;
            size += strlen(symbolPtr->contents) + 1;
           }
        }
     }


   GenWrite((void *) &numberOfUsedSymbols,(unsigned long) sizeof(unsigned long int),fp);
   GenWrite((void *) &size,(unsigned long) sizeof(unsigned long int),fp);

   for (i = 0; i < SYMBOL_HASH_SIZE; i++)
     {
      for (symbolPtr = symbolArray[i];
           symbolPtr != NULL;
           symbolPtr = symbolPtr->next)
        {
         if (symbolPtr->neededSymbol)
           {
            length = strlen(symbolPtr->contents) + 1;
            GenWrite((void *) symbolPtr->contents,(unsigned long) length,fp);
           }
        }
     }
  }
