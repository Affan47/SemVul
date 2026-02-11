appendStr (const char *aCStr)
{
  int retVal = 0;
  int skip;

  if ( aCStr ) {
    skip = skipWS( aCStr );
    if ( skip && !mimeLabel.isEmpty() ) {
      if ( skip > 0 ) {
        mimeValue += QByteArray( aCStr, skip );
        aCStr += skip;
        retVal += skip;
        skip = parseFullLine( aCStr );
        mimeValue += QByteArray( aCStr, skip );
        retVal += skip;
        aCStr += skip;
      }
    } else {
      if ( mimeLabel.isEmpty() ) {
        return setStr( aCStr );
      }
    }
  }
  return retVal;
}
