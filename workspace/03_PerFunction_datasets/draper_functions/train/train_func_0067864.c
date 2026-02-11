getFileName(const char *fileName,
					 char *result, size_t resultLen)
{
  char separator;
#ifndef WIN32
  separator = '/';
#else
  separator = '\\';
#endif

  if (fileName == NULL || fileName[0] == '\0' || resultLen == 0)
  {
    ArLog::log(ArLog::Normal, "ArUtil: getFileName, bad setup");
    return false;
  }

  char *str;
  size_t fileNameLen = strlen(fileName);
  str = new char[fileNameLen + 1];


  strncpy(str, fileName, fileNameLen);

  str[fileNameLen] = '\0';


  char *toPos;
  ArUtil::fixSlashes(str, fileNameLen + 1);


  toPos = strrchr(str, separator);

  if (toPos == NULL)
  {

    strncpy(result, str, resultLen - 1);
    result[resultLen - 1] = '\0';

    delete[] str;
    return true;
  }

  else
  {
    strncpy(result, &str[toPos - str + 1], resultLen - 2);
    result[resultLen - 1] = '\0';

    delete[] str;
    return true;
  }
}
