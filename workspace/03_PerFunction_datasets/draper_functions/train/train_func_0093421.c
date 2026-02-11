CreateProjectFile(
                                     const std::vector<cmLocalGenerator*>& lgs)
{
  const cmMakefile* mf=lgs[0]->GetMakefile();
  std::string outputDir=mf->GetStartOutputDirectory();
  std::string projectName=mf->GetProjectName();

  std::string filename=outputDir+"/";
  filename+=projectName+".cbp";
  std::string sessionFilename=outputDir+"/";
  sessionFilename+=projectName+".layout";

  this->CreateNewProjectFile(lgs, filename);
}
