write ( tnstream& stream ) const
{
   stream.writeInt ( 15000 );
   stream.writeInt ( groupCount );
   stream.writeInt ( calculated );
   for ( int i = 0; i < groupCount; i++ )
      stream.writeFloat ( group[i] );
}
