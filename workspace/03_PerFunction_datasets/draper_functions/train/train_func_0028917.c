expandPath(origPath,expandedPath,maxLen)
String origPath;
String expandedPath;
unsigned int maxLen;
{

  if (!origPath) {
    return;
  }


  if (*origPath == '~' && *(origPath+1) == '/') {
    unsigned int origLen;
    String home          = getenv("HOME");
    origLen = (origPath ? strlen(origPath) : 0);


    if ( (maxLen - origLen - 1) >= strlen(home) ) {
      strcpy(expandedPath, home);
      strcat(expandedPath, origPath+1);
      return;
    }
  }
  strcpy(expandedPath, origPath);
}
