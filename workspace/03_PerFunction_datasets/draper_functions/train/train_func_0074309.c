fieldVisible( State state, const QString &fieldName ) const
{
  if ( state == Modify ) {
    if ( Auth::self()->group() == Auth::Users ) {
      if ( fieldName == "cyrus-userquota" )
        return false;
    }
  }

  return true;
}
