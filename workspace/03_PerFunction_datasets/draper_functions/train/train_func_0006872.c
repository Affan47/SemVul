write ( tnstream& stream ) const
{
   stream.writeInt ( terrain_version );
   stream.writeInt ( !name.empty() );
   stream.writeInt ( id );
   for ( int m = 0; m < cwettertypennum; m++ )
      stream.writeInt ( weather[m] != NULL );

   for ( int m = 0; m < 8; m++ )
      stream.writeInt ( 0 );

   stream.writeString( name );
   for ( int i = 0; i < cwettertypennum ; i++ )
      if ( weather[i] )
         weather[i]->write( stream );

   writeClassContainer( secondaryIDs, stream );


}
