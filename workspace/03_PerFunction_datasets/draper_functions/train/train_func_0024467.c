read ( tnstream& stream, int version )
{
   bool loadImage = true;
   if (version <=2 ) {
      loadImage = stream.readInt();

      for ( int j = 1; j < 8; j++ )
         stream.readInt();

      for ( int j = 0; j < 8; j++ )
         stream.readInt();
   }

   if ( version == 1 ) {
      stream.readInt();
      defensebonus = stream.readWord();
      attackbonus = stream.readWord();
      basicjamming = stream.readChar();
   } else {
      defensebonus = stream.readInt();
      attackbonus = stream.readInt();
      basicjamming = stream.readInt();
   }
   int move_maluscount = stream.readChar();
   stream.readInt();
   stream.readInt();
   stream.readInt();

   art.read ( stream );

   bi_pict = stream.readInt();
   for ( int j = 1; j < 6; j++ )
      stream.readInt();

   move_malus.read( stream, minmalq, move_maluscount );

   if ( version >= 5 )
      originalImageFilename = stream.readString();


   if ( loadImage )
      if ( bi_pict == -1 )
         image.read ( stream );
}
