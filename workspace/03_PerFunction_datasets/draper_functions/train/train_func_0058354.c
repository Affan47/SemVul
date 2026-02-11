LoadProgramFile(const char *pFilename, FILE *pFile,
                                    const char *pProcessorName)
{
  Processor * pProcessor = this;


  ProgramFileType * aFileTypes[] = {
    ProgramFileTypeList::GetList()[0],
    ProgramFileTypeList::GetList()[1]
  };
  if(IsFileExtension(pFilename,"cod")) {

    swap(aFileTypes[0], aFileTypes[1]);
  }
  int iReturn  = aFileTypes[0]->LoadProgramFile(&pProcessor, pFilename, pFile, pProcessorName);
  if (iReturn != ProgramFileType::SUCCESS) {
    fseek(pFile, 0, SEEK_SET);
    iReturn = aFileTypes[1]->LoadProgramFile(&pProcessor, pFilename, pFile, pProcessorName);
  }
  cout << "Leaving pic_processor::LoadProgramFile\n";
  return iReturn == ProgramFileType::SUCCESS;
}
