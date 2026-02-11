ShouldIDoCoverage(const char* file,
  const char* srcDir,
  const char* binDir)
{
  if(this->IsFilteredOut(file))
    {
    return false;
    }

  std::vector<cmsys::RegularExpression>::iterator sit;
  for ( sit = this->CustomCoverageExcludeRegex.begin();
    sit != this->CustomCoverageExcludeRegex.end(); ++ sit )
    {
    if ( sit->find(file) )
      {
      cmCTestLog(this->CTest, HANDLER_VERBOSE_OUTPUT, "  File " << file
        << " is excluded in CTestCustom.ctest" << std::endl;);
      return false;
      }
    }

  std::string fSrcDir = cmSystemTools::CollapseFullPath(srcDir);
  std::string fBinDir = cmSystemTools::CollapseFullPath(binDir);
  std::string fFile = cmSystemTools::CollapseFullPath(file);
  bool sourceSubDir = cmSystemTools::IsSubDirectory(fFile.c_str(),
    fSrcDir.c_str());
  bool buildSubDir = cmSystemTools::IsSubDirectory(fFile.c_str(),
    fBinDir.c_str());

  std::string fileDir = cmSystemTools::GetFilenamePath(fFile.c_str());
  std::string checkDir;


  if ( sourceSubDir && buildSubDir )
    {
    if ( fSrcDir.size() > fBinDir.size() )
      {
      checkDir = fSrcDir;
      }
    else
      {
      checkDir = fBinDir;
      }
    }
  else if ( sourceSubDir )
    {
    checkDir = fSrcDir;
    }
  else if ( buildSubDir )
    {
    checkDir = fBinDir;
    }
  std::string ndc
    = cmSystemTools::FileExistsInParentDirectories(".NoDartCoverage",
      fFile.c_str(), checkDir.c_str());
  if ( ndc.size() )
    {
    cmCTestLog(this->CTest, HANDLER_VERBOSE_OUTPUT, "Found: " << ndc.c_str()
      << " so skip coverage of " << file << std::endl);
    return false;
    }


  std::string relPath;
  if(checkDir.size() )
    {
    relPath = cmSystemTools::RelativePath(checkDir.c_str(),
                                          fFile.c_str());
    }
  else
    {
    relPath = fFile;
    }
  if ( checkDir == fSrcDir )
    {
    checkDir = fBinDir;
    }
  else
    {
    checkDir = fSrcDir;
    }
  fFile = checkDir + "/" + relPath;
  fFile = cmSystemTools::GetFilenamePath(fFile.c_str());

  if ( fileDir == fFile )
    {

    return true;
    }

  ndc = cmSystemTools::FileExistsInParentDirectories(".NoDartCoverage",
    fFile.c_str(), checkDir.c_str());
  if ( ndc.size() )
    {
    cmCTestLog(this->CTest, HANDLER_VERBOSE_OUTPUT, "Found: " << ndc.c_str()
      << " so skip coverage of: " << file << std::endl);
    return false;
    }

  return true;
}
