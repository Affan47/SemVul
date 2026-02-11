gm2(
  void *theEnv,
  unsigned int size)
  {
   struct memoryPtr *memPtr;

   if (size < sizeof(char *)) size = sizeof(char *);

   if (size >= MEM_TABLE_SIZE) return(genalloc(theEnv,(unsigned) size));

   memPtr = (struct memoryPtr *) MemoryData(theEnv)->MemoryTable[size];
   if (memPtr == NULL)
     {
      return(genalloc(theEnv,(unsigned) size));
     }

   MemoryData(theEnv)->MemoryTable[size] = memPtr->next;

   return ((void *) memPtr);
  }
