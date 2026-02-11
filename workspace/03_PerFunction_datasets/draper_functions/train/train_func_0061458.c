SlotNameHashTableToCode(
  void *theEnv,
  char *fileName,
  int fileID,
  FILE *headerFP,
  int imageID,
  int maxIndices,
  int *fileCount)
  {
   FILE *slotNameHashFile = NULL;
   int slotNameHashArrayCount,
       slotNameHashArrayVersion = 1;

   slotNameHashFile = OpenFileIfNeeded(theEnv,slotNameHashFile,fileName,fileID,
                                       imageID,fileCount,
                                       slotNameHashArrayVersion,headerFP,
                                       "SLOT_NAME *",SlotNameHashPrefix(),FALSE,NULL);
   if (slotNameHashFile == NULL)
     return(FALSE);
   for (slotNameHashArrayCount = 0 ;
        slotNameHashArrayCount < SLOT_NAME_TABLE_HASH_SIZE ;
        slotNameHashArrayCount++)
     {
      if (slotNameHashArrayCount > 0)
        fprintf(slotNameHashFile,",\n");
      PrintSlotNameReference(theEnv,slotNameHashFile,DefclassData(theEnv)->SlotNameTable[slotNameHashArrayCount],
                             imageID,maxIndices);
     }
   CloseFileIfNeeded(theEnv,slotNameHashFile,&slotNameHashArrayCount,
                                        &slotNameHashArrayVersion,slotNameHashArrayCount,
                                        NULL,NULL);
   return(TRUE);
  }
