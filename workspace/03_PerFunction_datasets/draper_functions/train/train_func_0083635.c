ConstructToCode(
  void *theEnv,
  char *fileName,
  int fileID,
  FILE *headerFP,
  int imageID,
  int maxIndices)
  {
   int fileCount = 1;
   struct defmodule *theModule;
   struct defglobal *theDefglobal;
   int moduleCount = 0, moduleArrayCount = 0, moduleArrayVersion = 1;
   int defglobalArrayCount = 0, defglobalArrayVersion = 1;
   FILE *moduleFile = NULL, *defglobalFile = NULL;


   fprintf(headerFP,"#include \"globldef.h\"\n");


   for (theModule = (struct defmodule *) EnvGetNextDefmodule(theEnv,NULL);
        theModule != NULL;
        theModule = (struct defmodule *) EnvGetNextDefmodule(theEnv,theModule))
     {
      EnvSetCurrentModule(theEnv,(void *) theModule);

      moduleFile = OpenFileIfNeeded(theEnv,moduleFile,fileName,fileID,imageID,&fileCount,
                                    moduleArrayVersion,headerFP,
                                    "struct defglobalModule",ModulePrefix(DefglobalData(theEnv)->DefglobalCodeItem),
                                    FALSE,NULL);

      if (moduleFile == NULL)
        {
         CloseDefglobalFiles(theEnv,moduleFile,defglobalFile,maxIndices);
         return(0);
        }

      DefglobalModuleToCode(theEnv,moduleFile,theModule,imageID,maxIndices,moduleCount);
      moduleFile = CloseFileIfNeeded(theEnv,moduleFile,&moduleArrayCount,&moduleArrayVersion,
                                     maxIndices,NULL,NULL);

      for (theDefglobal = (struct defglobal *) EnvGetNextDefglobal(theEnv,NULL);
           theDefglobal != NULL;
           theDefglobal = (struct defglobal *) EnvGetNextDefglobal(theEnv,theDefglobal))
        {
         defglobalFile = OpenFileIfNeeded(theEnv,defglobalFile,fileName,fileID,imageID,&fileCount,
                                         defglobalArrayVersion,headerFP,
                                         "struct defglobal",ConstructPrefix(DefglobalData(theEnv)->DefglobalCodeItem),
                                         FALSE,NULL);
         if (defglobalFile == NULL)
           {
            CloseDefglobalFiles(theEnv,moduleFile,defglobalFile,maxIndices);
            return(0);
           }

         DefglobalToCode(theEnv,defglobalFile,theDefglobal,imageID,maxIndices,moduleCount);
         defglobalArrayCount++;
         defglobalFile = CloseFileIfNeeded(theEnv,defglobalFile,&defglobalArrayCount,
                                           &defglobalArrayVersion,maxIndices,NULL,NULL);
        }

      moduleCount++;
      moduleArrayCount++;
     }

   CloseDefglobalFiles(theEnv,moduleFile,defglobalFile,maxIndices);

   return(1);
  }
