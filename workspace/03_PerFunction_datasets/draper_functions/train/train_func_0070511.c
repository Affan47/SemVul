Generate()
{

  this->cmGlobalGenerator::Generate();


  unsigned long total = 0;
  for(ProgressMapType::const_iterator pmi = this->ProgressMap.begin();
      pmi != this->ProgressMap.end(); ++pmi)
    {
    total += pmi->second.NumberOfActions;
    }


  unsigned long current = 0;
  for(ProgressMapType::iterator pmi = this->ProgressMap.begin();
      pmi != this->ProgressMap.end(); ++pmi)
    {
    pmi->second.WriteProgressVariables(total, current);
    }
  for(unsigned int i = 0; i < this->LocalGenerators.size(); ++i)
    {
    cmLocalUnixMakefileGenerator3 *lg =
      static_cast<cmLocalUnixMakefileGenerator3 *>(this->LocalGenerators[i]);
    std::string markFileName = lg->GetMakefile()->GetStartOutputDirectory();
    markFileName += "/";
    markFileName += cmake::GetCMakeFilesDirectory();
    markFileName += "/progress.marks";
    cmGeneratedFileStream markFile(markFileName.c_str());
    markFile << this->CountProgressMarksInAll(lg) << "\n";
    }


  this->WriteMainMakefile2();
  this->WriteMainCMakefile();
}
