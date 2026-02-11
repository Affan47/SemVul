updateJobList(
  OFList<printJob *>&jobList,
  DVInterface &dvi,
  OFBool& terminateFlag,
  const char *filenamePrefix)
{
  if (filenamePrefix==NULL) return EC_IllegalCall;
  OFString prefix = filenamePrefix;
  OFString postfix = PRINTJOB_SUFFIX;
  size_t prefixSize = prefix.size();
  size_t postfixSize = postfix.size();
  OFString currentName;
  OFString jobName;
  OFString renameName;
  printJob *currentJob = NULL;
  OFBool currentTerminate = OFFalse;
  OFCondition result = EC_Normal;
  const char *spoolFolder = dvi.getSpoolFolder();

#ifdef HAVE_WINDOWS_H
  WIN32_FIND_DATA stWin32FindData;
  OFString currentdir = spoolFolder;
  currentdir += "\\*";

  HANDLE hFile = FindFirstFile(currentdir.c_str(), &stWin32FindData);
  int ret = (hFile != INVALID_HANDLE_VALUE);
  while (ret)
  {
      currentName = stWin32FindData.cFileName;
#else
  DIR *dirp = NULL;
  struct dirent *dp = NULL;
  if ((dirp = opendir(spoolFolder)) != NULL)
  {
    for (dp=readdir(dirp);((result == EC_Normal)&&(dp != NULL)); dp=readdir(dirp))
    {
      currentName = dp->d_name;
#endif
      if ((prefix == currentName.substr(0, prefixSize)) &&
          (currentName.size() > postfixSize) &&
          (postfix == currentName.substr(currentName.size()-postfixSize)))
      {

        jobName = spoolFolder;
        jobName += PATH_SEPARATOR;
        jobName += currentName;
        renameName = jobName;
        renameName += PRINTJOB_DONE_SUFFIX;
        currentJob = new printJob();
        if (currentJob)
        {
          currentTerminate = OFFalse;
          result = readJobFile(jobName.c_str(), renameName.c_str(), *currentJob, currentTerminate);
          if (currentTerminate) terminateFlag = OFTrue;
          if (EC_Normal == result)
          {

            if (!currentTerminate) jobList.push_back(currentJob); else delete currentJob;
          }
          else
          {
            delete currentJob;
            OFLOG_ERROR(dcmprscuLogger, "spooler: parsing of job file '" << jobName.c_str() << "' failed");
          }
        } else result = EC_MemoryExhausted;
      }

#ifdef HAVE_WINDOWS_H
      ret = FindNextFile(hFile, &stWin32FindData);
  }
  if(hFile != INVALID_HANDLE_VALUE)
  {
    FindClose(hFile);
#else
    }
    closedir(dirp);
#endif
  } else {
    OFLOG_ERROR(dcmprscuLogger, "unable to read spool directory '" << spoolFolder << "'");
    result = EC_IllegalCall;
  }
  return result;
}
