readContactGroupReference(
  ContactGroup::ContactGroupReference &reference )
{
  const QXmlStreamAttributes elementAttributes = attributes();
  const QStringRef uid = elementAttributes.value( QLatin1String( "uid" ) );
  if ( uid.isEmpty() ) {
    raiseError( QLatin1String( "ContactGroupReference is missing a uid" ) );
    return false;
  }

  reference.setUid( uid.toString() );

  return true;
}
