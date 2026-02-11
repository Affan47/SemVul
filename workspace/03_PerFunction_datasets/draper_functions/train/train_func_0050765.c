FactPatternNodeReference(
  void *theEnv,
  void *theVPattern,
  FILE *theFile,
  int imageID,
  int maxIndices)
  {
   struct factPatternNode *thePattern = (struct factPatternNode *) theVPattern;

   if (thePattern == NULL) fprintf(theFile,"NULL");
   else
     {
      fprintf(theFile,"&%s%d_%ld[%ld]",FactPrefix(),
                    imageID,(thePattern->bsaveID / maxIndices) + 1,
                            thePattern->bsaveID % maxIndices);
     }
  }
