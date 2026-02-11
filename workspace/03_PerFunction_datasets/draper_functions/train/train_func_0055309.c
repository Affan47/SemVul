loadPBEMServerDefaults()
{
      if ( !pbemserver )
         pbemserver = new PBEMServer();


      PG_LineEdit* le = dynamic_cast<PG_LineEdit*>( FindChild( "Server", true ));
      if ( le )
         le->SetText( PBEMServer::getDefaultServerAddress() );

}
