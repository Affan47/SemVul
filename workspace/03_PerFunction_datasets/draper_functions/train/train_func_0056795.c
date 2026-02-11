PrintDefmoduleReference(
  void *theEnv,
  FILE *theFile,
  struct defmodule *theModule)
  {
   if (theModule == NULL) fprintf(theFile,"NULL");
   else fprintf(theFile,"&%s%d_%ld[%ld]",DefmodulePrefix(),ConstructCompilerData(theEnv)->ImageID,
                                    (long) ((theModule->bsaveID / ConstructCompilerData(theEnv)->MaxIndices) + 1),
                                    (long) (theModule->bsaveID % ConstructCompilerData(theEnv)->MaxIndices));
  }
