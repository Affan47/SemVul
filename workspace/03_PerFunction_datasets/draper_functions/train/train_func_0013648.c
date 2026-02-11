read ( tnstream& stream ) {
   terrain.read ( stream );
   terrain.reset( 7 );
   terrainreq.read ( stream );
   terrainnot.read ( stream );
   terrainnot.reset( 7 );
   terrainkill.read ( stream );

   for ( int a = 0; a < 10; a++ )
       stream.readInt( );
}
