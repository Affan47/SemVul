IntegerHashNodesToCode(
  void *theEnv,
  char *fileName,
  int version)
  {
   int i, j;
   struct integerHashNode *hashPtr;
   int count;
   int numberOfEntries;
   struct integerHashNode **integerTable;
   int newHeader = TRUE;
   FILE *fp;
   int arrayVersion = 1;


   integerTable = GetIntegerTable(theEnv);
   count = numberOfEntries = 0;

   for (i = 0; i < INTEGER_HASH_SIZE; i++)
     {
      for (hashPtr = integerTable[i];
           hashPtr != NULL;
           hashPtr = hashPtr->next)
        { numberOfEntries++; }
     }

   if (numberOfEntries == 0) return(version);

   for (i = 1; i <= (numberOfEntries / ConstructCompilerData(theEnv)->MaxIndices) + 1 ; i++)
     { fprintf(ConstructCompilerData(theEnv)->HeaderFP,"extern struct integerHashNode I%d_%d[];\n",ConstructCompilerData(theEnv)->ImageID,i); }


   if ((fp = NewCFile(theEnv,fileName,1,version,FALSE)) == NULL) return(-1);


   j = 0;

   for (i = 0; i < INTEGER_HASH_SIZE; i++)
     {
      for (hashPtr = integerTable[i];
           hashPtr != NULL;
           hashPtr = hashPtr->next)
        {
         if (newHeader)
           {
            fprintf(fp,"struct integerHashNode I%d_%d[] = {\n",ConstructCompilerData(theEnv)->ImageID,arrayVersion);
            newHeader = FALSE;
           }

         if (hashPtr->next == NULL)
           { fprintf(fp,"{NULL,"); }
         else
           {
            if ((j + 1) >= ConstructCompilerData(theEnv)->MaxIndices)
              { fprintf(fp,"{&I%d_%d[%d],",ConstructCompilerData(theEnv)->ImageID,arrayVersion + 1,0); }
            else
              { fprintf(fp,"{&I%d_%d[%d],",ConstructCompilerData(theEnv)->ImageID,arrayVersion,j + 1); }
           }

         fprintf(fp,"%ld,0,1,0,0,%d,",hashPtr->count + 1,i);
         fprintf(fp,"%ld",hashPtr->contents);

         count++;
         j++;

         if ((count == numberOfEntries) || (j >= ConstructCompilerData(theEnv)->MaxIndices))
           {
            fprintf(fp,"}};\n");
            GenClose(theEnv,fp);
            j = 0;
            version++;
            arrayVersion++;
            if (count < numberOfEntries)
              {
               if ((fp = NewCFile(theEnv,fileName,1,version,FALSE)) == NULL) return(0);
               newHeader = TRUE;
              }
           }
         else
           { fprintf(fp,"},\n"); }
        }
     }

   return(version);
  }
