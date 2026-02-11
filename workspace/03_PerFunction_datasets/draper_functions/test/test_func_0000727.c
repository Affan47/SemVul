InitializeAtomTables(
  void *theEnv,
  struct symbolHashNode **symbolTable,
  struct floatHashNode **floatTable,
  struct integerHashNode **integerTable,
  struct bitMapHashNode **bitmapTable)
  {
#if ! RUN_TIME
#if MAC_MCW || IBM_MCW || MAC_XCD
#pragma unused(symbolTable)
#pragma unused(floatTable)
#pragma unused(integerTable)
#pragma unused(bitmapTable)
#endif
   unsigned long i;
#endif

   AllocateEnvironmentData(theEnv,SYMBOL_DATA,sizeof(struct symbolData),DeallocateSymbolData);

#if ! RUN_TIME


   SymbolData(theEnv)->SymbolTable = (SYMBOL_HN **)
                  gm3(theEnv,sizeof (SYMBOL_HN *) * SYMBOL_HASH_SIZE);

   SymbolData(theEnv)->FloatTable = (FLOAT_HN **)
                  gm2(theEnv,(int) sizeof (FLOAT_HN *) * FLOAT_HASH_SIZE);

   SymbolData(theEnv)->IntegerTable = (INTEGER_HN **)
                   gm2(theEnv,(int) sizeof (INTEGER_HN *) * INTEGER_HASH_SIZE);

   SymbolData(theEnv)->BitMapTable = (BITMAP_HN **)
                   gm2(theEnv,(int) sizeof (BITMAP_HN *) * BITMAP_HASH_SIZE);


   for (i = 0; i < SYMBOL_HASH_SIZE; i++) SymbolData(theEnv)->SymbolTable[i] = NULL;
   for (i = 0; i < FLOAT_HASH_SIZE; i++) SymbolData(theEnv)->FloatTable[i] = NULL;
   for (i = 0; i < INTEGER_HASH_SIZE; i++) SymbolData(theEnv)->IntegerTable[i] = NULL;
   for (i = 0; i < BITMAP_HASH_SIZE; i++) SymbolData(theEnv)->BitMapTable[i] = NULL;


   SymbolData(theEnv)->TrueSymbolHN = EnvAddSymbol(theEnv,TRUE_STRING);
   IncrementSymbolCount(SymbolData(theEnv)->TrueSymbolHN);
   SymbolData(theEnv)->FalseSymbolHN = EnvAddSymbol(theEnv,FALSE_STRING);
   IncrementSymbolCount(SymbolData(theEnv)->FalseSymbolHN);
   SymbolData(theEnv)->PositiveInfinity = EnvAddSymbol(theEnv,POSITIVE_INFINITY_STRING);
   IncrementSymbolCount(SymbolData(theEnv)->PositiveInfinity);
   SymbolData(theEnv)->NegativeInfinity = EnvAddSymbol(theEnv,NEGATIVE_INFINITY_STRING);
   IncrementSymbolCount(SymbolData(theEnv)->NegativeInfinity);
   SymbolData(theEnv)->Zero = EnvAddLong(theEnv,0L);
   IncrementIntegerCount(SymbolData(theEnv)->Zero);
#else
   SetSymbolTable(theEnv,symbolTable);
   SetFloatTable(theEnv,floatTable);
   SetIntegerTable(theEnv,integerTable);
   SetBitMapTable(theEnv,bitmapTable);
#endif
  }
