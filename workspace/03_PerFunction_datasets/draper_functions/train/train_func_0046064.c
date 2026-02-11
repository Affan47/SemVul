writeData( const ContactGroup::Data &data )
{
  writeStartElement( QLatin1String( "contactData" ) );
  writeAttribute( QLatin1String( "name" ), data.name() );
  writeAttribute( QLatin1String( "email" ), data.email() );


  writeEndElement();
}
