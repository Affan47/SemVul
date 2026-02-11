HandlersToCode(
  void *theEnv,
  FILE **handlerFile,
  char *fileName,
  int fileID,
  int imageID,
  FILE *headerFP,
  int *fileCount,
  int maxIndices,
  DEFCLASS *theDefclass,
  int *handlerArrayVersion,
  int *handlerArrayCount,
  int *reopenHandlerFile,
  struct CodeGeneratorFile *handlerCodeFile)
  {
   register unsigned i;
   HANDLER *hnd;

   if (theDefclass->handlerCount == 0)
     return(TRUE);

   *handlerFile = OpenFileIfNeeded(theEnv,*handlerFile,fileName,fileID,
                                        imageID,fileCount,
                                        *handlerArrayVersion,headerFP,
                                        "HANDLER",HandlerPrefix(),*reopenHandlerFile,
                                        handlerCodeFile);
   if (*handlerFile == NULL)
     return(FALSE);

   for (i = 0 ; i < theDefclass->handlerCount ; i++)
     {
      if (i > 0)
        fprintf(*handlerFile,",\n");
      hnd = &theDefclass->handlers[i];
      fprintf(*handlerFile,"{ %u,%u,0,0,0,",hnd->system,hnd->type);
      PrintSymbolReference(theEnv,*handlerFile,hnd->name);
      fprintf(*handlerFile,",");
      PrintClassReference(theEnv,*handlerFile,hnd->cls,imageID,maxIndices);
      fprintf(*handlerFile,",%d,%d,%d,",hnd->minParams,hnd->maxParams,
                                        hnd->localVarCount);
      ExpressionToCode(theEnv,*handlerFile,hnd->actions);
      fprintf(*handlerFile,",NULL }");
     }
   *handlerArrayCount += (int) theDefclass->handlerCount;
   *handlerFile = CloseFileIfNeeded(theEnv,*handlerFile,handlerArrayCount,
                                    handlerArrayVersion,maxIndices,
                                    reopenHandlerFile,handlerCodeFile);
   return(TRUE);
  }
