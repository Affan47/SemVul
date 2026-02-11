writeStorage( tnstream& stream ) const
{
   stream.writeInt( taskMagic );
   for ( int i = 0; i < GameMap::maxTotalPlayers; ++i ) {
      if ( playerTasks[i] ) {
         stream.writeInt( 1 );
         playerTasks[i]->writetostream( &stream );
      } else
         stream.writeInt( 0 );
   }
   stream.writeInt( taskMagic );
   if ( newTasks ) {
      stream.writeInt( 1 );
      newTasks->writetostream( &stream );
   } else
      stream.writeInt( 0 );

   stream.writeInt( lastPlayer );
   stream.writeInt( taskMagic );

}
