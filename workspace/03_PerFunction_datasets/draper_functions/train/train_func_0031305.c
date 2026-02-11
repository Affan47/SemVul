File_DoesFileExtensionMatch(char *pszFileName, char *pszExtension)
{
  if ( strlen(pszFileName) < strlen(pszExtension) )
    return(false);

  if ( !strcasecmp(&pszFileName[strlen(pszFileName)-strlen(pszExtension)], pszExtension) )
    return(true);


  return(false);
}
