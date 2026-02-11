ArgusDeleteModeler()
{
   ArgusModelerCleanUp ();
   ArgusDeleteQueue (ArgusFlowQueue);

   if (ArgusModel)
      ArgusFree(ArgusModel);

   if (ArgusHashTable.array)
      ArgusFree(ArgusHashTable.array);

   if (ArgusModelerOutputSocket) {
      while (ArgusModelerOutputSocket->ArgusOutputList->count)
         if (ArgusWriteOutSocket(ArgusModelerOutputSocket) < 0)
            break;
   }

#ifdef ARGUSDEBUG
   ArgusDebug (1, "ArgusDeleteModeler() ArgusModeler 0x%x, HashArray 0x%x\n",
                 ArgusModel, ArgusHashTable.array);
#endif
}
