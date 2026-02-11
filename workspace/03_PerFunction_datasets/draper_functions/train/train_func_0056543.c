defaultEncoding() const
{
  QString encoding = settings()->encoding();
  if ( !encoding.isEmpty() )
    return encoding;


  if ( url().protocol().startsWith( "http" ) )
    return "iso-8859-1";
  else
    return KGlobal::locale()->encoding();
}
