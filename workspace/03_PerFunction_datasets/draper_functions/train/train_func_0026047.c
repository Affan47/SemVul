InitAtomicValueNeededFlags(
  void *theEnv)
  {
   unsigned long i;
   SYMBOL_HN *symbolPtr, **symbolArray;
   FLOAT_HN *floatPtr, **floatArray;
   INTEGER_HN *integerPtr, **integerArray;
   BITMAP_HN *bitMapPtr, **bitMapArray;


   symbolArray = GetSymbolTable(theEnv);

   for (i = 0; i < SYMBOL_HASH_SIZE; i++)
     {
      symbolPtr = symbolArray[i];
      while (symbolPtr != NULL)
        {
         symbolPtr->neededSymbol = FALSE;
         symbolPtr = symbolPtr->next;
        }
     }


   floatArray = GetFloatTable(theEnv);

   for (i = 0; i < FLOAT_HASH_SIZE; i++)
     {
      floatPtr = floatArray[i];
      while (floatPtr != NULL)
        {
         floatPtr->neededFloat = FALSE;
         floatPtr = floatPtr->next;
        }
     }


   integerArray = GetIntegerTable(theEnv);

   for (i = 0; i < INTEGER_HASH_SIZE; i++)
     {
      integerPtr = integerArray[i];
      while (integerPtr != NULL)
        {
         integerPtr->neededInteger = FALSE;
         integerPtr = integerPtr->next;
        }
     }


   bitMapArray = GetBitMapTable(theEnv);

   for (i = 0; i < BITMAP_HASH_SIZE; i++)
     {
      bitMapPtr = bitMapArray[i];
      while (bitMapPtr != NULL)
        {
         bitMapPtr->neededBitMap = FALSE;
         bitMapPtr = bitMapPtr->next;
        }
     }
  }
