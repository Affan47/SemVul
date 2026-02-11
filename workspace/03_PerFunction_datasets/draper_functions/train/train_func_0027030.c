parseWord (const char *aCStr)
{
  int retVal = 0;

  if ( aCStr && *aCStr ) {
    if ( *aCStr == '"' ) {
      return mimeHdrLine::parseQuoted( '"', '"', aCStr );
    } else {
      return mimeHdrLine::parseHalfWord( aCStr );
    }
  } else {

  }
  return retVal;
}
