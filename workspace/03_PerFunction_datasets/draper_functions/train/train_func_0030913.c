registerChilds( CargoDialog* cd )
{
   widget = cd->FindChild( getASCTXTname(), true);
   if ( !widget )
      warningMessage( "Could not find widget with name " + getASCTXTname() );
}
